Activity and Operation Modules
==============================

This document provides an overview of concepts that developers should 
know when developing Activity and Operation modules.

.. note::
   Every Activity must include at least one Operation and at least one Job.

Naming Conventions (Activity)
-----------------------------
*composer.json*

* The *name* parameter should be of the form 
  [application name or vendor name]/activity-[bundle purpose].
  
  *Example: campaignchain/activity-twitter*

* The *type* parameter should be 'campaignchain-activity'.

*campaignchain.yml*

* The name of an Activity module should follow the convention 
  [application name or vendor name]-[channel name]-[bundle purpose]. 
  
  *Example: campaignchain-twitter-update-status*

Naming Conventions (Operation)
------------------------------
*composer.json*

* The *name* parameter should be of the form 
  [application name or vendor name]/operation-[bundle purpose]. 
  
  *Example: campaignchain/operation-twitter*

* The *type* parameter should be 'campaignchain-operation'.

*campaignchain.yml*

* The name of an Operation module should follow the convention 
  [application name or vendor name]-[channel name]-[operation descriptor]. 
  
  *Example: campaignchain-twitter-update-status*

Linking Activities and Channels
-------------------------------
The Activity bundle's *campaignchain.yml* file should contain a
*channels* parameter, which specifies the link between the Channel and the
Activity. The *channels* parameter should be of the form 
[channel bundle name]/[channel module name]

*Example: 'acme/channel-linkedin/acme-linkedin' refers to the Channel bundle 
'acme/channel-linkedin' and the Channel module within it named 'acme-linkedin'.*

Wizards and Routes
------------------
CampaignChain provides a set of "wizards" that ease integration of your module
into the CampaignChain GUI. The Activity Wizard takes care of presenting the user
with a form that lists available campaigns, channels and operations. Based 
on the user's selection in the form, the Activity Wizard is able to retrieve 
and display the available Operations for the selected Channel and link it 
to the selected Campaign.

The Activity Wizard can be invoked from within a controller using the service 
identifier 'campaignchain.core.activity.wizard' as shown below.

::

  <?php
  // invoke and use activity wizard
  $wizard = $this->get('campaignchain.core.activity.wizard');
  $campaign = $wizard->getCampaign();
  $activity = $wizard->getActivity();


The routes and display name used by the Activity Wizard are obtained from 
the module configuration in the Activity bundle's *campaignchain.yml* file:

.. code-block:: yaml

  modules:
    campaignchain-linkedin-share-news-item:
        display_name: 'Share News'
        channels:
            - campaignchain/channel-linkedin/campaignchain-linkedin
        routes:
            new: campaignchain_activity_linkedin_share_news_item_new
            edit: campaignchain_activity_linkedin_share_news_item_edit
            edit_modal: campaignchain_activity_linkedin_share_news_item_edit_modal
            edit_api: campaignchain_activity_linkedin_share_news_item_edit_api
        hooks:
            campaignchain-due: true

Activities with a Single Operation
----------------------------------
If an Activity has only one Operation, this should be made explicit by calling 
the Activity object's setEqualsOperation() method, as shown below:

::

  <?php
  $wizard = $this->get('campaignchain.core.activity.wizard');
  $activity = $wizard->getActivity();
  $activity->setEqualsOperation(true);

Operation Form
--------------
When a user defines a new operation, CampaignChain renders a form with fields appropriate
to that operation. This form must be included within the Operation module. 
The easiest way to create this form is by using Symfony's Form component 
and FormBuilder interface to define a Form object, as shown below:

::

  <?php
  use Symfony\Component\Form\AbstractType;
  use Symfony\Component\Form\FormBuilderInterface;
  use Symfony\Component\OptionsResolver\OptionsResolverInterface;
  use Symfony\Component\DependencyInjection\ContainerInterface;

  class ShareNewsItemOperationType extends AbstractType
  {

      public function buildForm(FormBuilderInterface $builder, array $options)
      {
          $builder
              ->add('message', 'text', array(
                  'property_path' => 'message',
                  'label' => 'Message',
                  'attr' => array(
                      'placeholder' => 'Add message...',
                      'max_length' => 200
                  )
              ));

          $builder
              ->add('submitUrl', 'text', array(
                  'property_path' => 'linkUrl',
                  'label' => 'URL of page being shared',
                  'attr' => array(
                      'placeholder' => 'Add URL...',
                      'max_length' => 255
                  )
              ));  

          // ... and so on //

      }
  }

This Form object can then be used within controller action methods to create 
or edit a new operation, as shown below:

::

  <?php  
  $activityType = $this->get('campaignchain.core.form.type.activity');
  $shareNewsItemOperation = new ShareNewsItemOperationType(
     $this->getDoctrine()->getManager(), $this->get('service_container')
  );
  $operationForms[] = array(
     'identifier' => self::OPERATION_IDENTIFIER,
     'form' => $shareNewsItemOperation,
     'label' => 'LinkedIn Message',
  );
  $activityType->setOperationForms($operationForms);

  $form = $this->createForm($activityType, $activity);
  $form->handleRequest($request);

  if ($form->isValid()) { 
        // process input
  }


Operation Module and Service
----------------------------

The Activity object's *addOperation()* method should be passed an Operation
object representing the operation to be added to the activity. CampaignChain's
Operation service can be used to retrieve the correct Operation module, 
using the Operation bundle name and module identifier. The Operation service 
is available using the identifier 'campaignchain.core.operation'.

::

  <?php
  $operationService = $this->get('campaignchain.core.operation');
  $operationModule = $operationService->getOperationModule(
    'campaignchain/operation-linkedin', 'campaignchain-linkedin-share-news-item'
  );

  $operation = new Operation();
  $operation->setName($activity->getName());
  $operation->setActivity($activity);
  $activity->addOperation($operation);

In this example, the Operation service finds the Operation module named 
'campaignchain-linkedin-share-news-item' in the bundle named 'campaignchain/operation-linkedin'.

Jobs
----

Every Operation module should include a Job, which actually executes the 
operation. This Job should implement the JobServiceInterface, which mandates 
an *execute()* method that is called when the job is executed. The Job is 
invoked by the CampaignChain scheduler when an Operation becomes due; it can also
be invoked manually to execute an operation immediately.

Hooks
-----

To process the hooks associated with an Activity, CampaignChain makes a Hook
service available, via the service name 'campaignchain.core.hook'. Call this service's
*processHooks()* method to process the hooks for an Activity, as shown below:

::

  <?php
  $hookService = $this->get('campaignchain.core.hook');
  $activity = $hookService->processHooks(
    self::BUNDLE_NAME, self::MODULE_IDENTIFIER, $activity, $data
  );


Operations and Locations
------------------------
An Operation can create a new Location as its end result and/or it can include 
CTAs that point to Locations. For example, a LinkedIn news sharing Operation 
would create a new Location - a Linkedin status message that is directly 
accessible via a unique URL.

When you create a new Activity within CampaignChain, your Operation should also
create a Location entry. At the time the Activity is created, the Location 
entry will necessarily be incomplete as the URL to the Location will not be 
known. 

Once the Operation is executed, the Job that executes it must update the 
Location with the URL. It must also change the Location's status from 
'STATUS_UNPUBLISHED' to 'STATUS_ACTIVE'.

It's important to define the *owns_location* parameter in the Operation module's 
*campaignchain.yml* file as shown below:

.. code-block:: yaml

  modules:
    campaignchain-linkedin-share-news-item:
        display_name: 'Share News'
        owns_location: true
        services:
            job: campaignchain.operation.linkedin.job.share_news_item


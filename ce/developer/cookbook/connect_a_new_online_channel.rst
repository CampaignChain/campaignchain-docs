Connect A New Online Channel
============================

The tutorial will walk you through the process of adding support for a new 
online channel - in this case, the online professional network `XING`_ - to 
CampaignChain by creating and programming the necessary modules and packaging 
them into a Symfony bundle.

The new XING modules will include functionality to connect to a user's 
XING activity stream and post updates to it.

Assumptions and Prerequisites
-----------------------------
* You have a `Symfony environment`_ meeting all the system requirements.
* You have a working :doc:`CampaignChain development installation </ce/administrator/installation/dev>`.
* You have a good understanding of the OAuth authentication process.
* You have a good understanding of the XING REST API. 
  `Learn more about the API`_.
* You have an application registered with XING and have obtained the 
  necessary keys. `Register your application`_.
* You have an account registered with XING, or you have access to the 
  :doc:`CampaignChain live development environment </ce/developer/book/development_environment>` (optional, for testing).

Overview
--------
To connect a new online channel through CampaignChain, here are the steps 
you will follow:

1. `Generate Channel and Location modules`_
2. `Create Channel and Location controllers and views`_
3. `Add a channel icon`_

To enable activities and operations for the new channel, here are the steps 
you will follow:

1. `Generate Operation and Activity modules`_
2. `Understand the API exposed by the channel you're connecting`_
3. `Create entities and entity managers for your Activities and Operations`_
4. `Create input forms and connect them to your entities`_
5. `Create an API client and operation processor`_
6. `Define an Activity handler`_
7. `Collect metrics and create a report processor`_

Connect Channels and Locations
------------------------------

.. _Generate Channel and Location modules:

1. Generate Channel and Location modules
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The first step is to create Channel and Location modules for the XING channel. 
In this case, we'll assume the organization name is Acme, and use this 
organization name for the module namespaces. 

The easiest way to generate these modules is with the CampaignChain module 
generator (included when you install with Composer and the option *--dev*).  
The commands below walk you through the process of generating a new Channel 
module. Note that you're safe using the defaults for all interactive 
prompts except for certain items shown below.

.. code-block:: bash

  $ php app/console campaignchain:generate:module
  Module type: Channel
  Vendor name: Acme
  Module name: Xing
  Module name suffix: 
  Module display name: XING
  Module description: This module connects to XING
  Author name: Acme Inc.
  Author's email address: info@acme.example.com
  Package license: Apache-2.0
  Package description: XING module for CampaignChain
  Package website URL: http://acme.example.com
  
Symfony will now produce a new bundle containing stub code and files, in 
the location *your-project/src/Acme/Channel/XingBundle*. The name of the 
bundle will be *AcmeChannelXingBundle*.

Channels go hand-in-hand with Locations. Typically, a Location in a Channel 
refers to a specific user's activity stream or profile. In this tutorial, 
the Location will be the user's XING news stream. 

Follow the steps above to generate a similar bundle for a Location in the 
Channel, remembering to specify the "Module type" as "Location" this time. The new 
bundle will be created at *your-project/src/Acme/Location/XingBundle* with 
the name *AcmeLocationXingBundle*.

.. note::
   Most of the code you see in the next few sections is automatically generated 
   for you by the CampaignChain module generator. You only need to copy and 
   paste the parts that are specific to the channel you're trying to 
   connect (in this example, XING).

.. _Create Channel and Location controllers and views:
   
2. Add Controllers and Views
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The Channel module takes care of creating a new Location and handling 
authentication between CampaignChain and the channel. The Channel module's 
auto-generated *campaignchain.yml* file specifies the routes and hooks 
used by its modules. Here's what the file looks like:

.. code-block:: yaml

    # src/Acme/Channel/XingBundle/campaignchain.yml
    
    modules:
        acme-xing:
            display_name: Xing
            description: This module connects to Xing
            routes: 
                new: acme_channel_xing_create
            hooks:
                default:
                
Notice the name of the Symfony route for creating a new channel. The 
corresponding URL and controller is defined in the module's auto-generated 
*routing.yml* file, as shown below:

.. code-block:: yaml

    # src/Acme/Channel/XingBundle/Resources/config/routing.yml
    
    acme_channel_xing_create:
        pattern: /channel/xing/create
        defaults: { _controller: AcmeChannelXingBundle:Xing:create }

To begin, define this controller and action:

::

  <?php
  // src/Acme/Channel/XingBundle/Controller/XingController.php

  namespace Acme\Channel\XingBundle\Controller;
  use CampaignChain\CoreBundle\Entity\Location;
  use Acme\Location\XingBundle\Entity\XingUser;
  use Symfony\Bundle\FrameworkBundle\Controller\Controller;
  use Symfony\Component\HttpFoundation\Request;
  use Symfony\Component\HttpFoundation\Session\Session;
  
  class XingController extends Controller
  {
      const RESOURCE_OWNER = 'Xing';
      
      const LOCATION_BUNDLE = 'acme/location-xing';
      
      const LOCATION_MODULE = 'acme-xing';
      
      private $applicationInfo = array(
          'key_labels' => array('key', 'Consumer key'),
          'secret_labels' => array('secret', 'Consumer secret'),
          'config_url' => 'https://dev.xing.com/applications/dashboard',
          'parameters' => array(),
          'wrapper' => array(
              'class'=>'Hybrid_Providers_XING',
              'path' => 'vendor/hybridauth/hybridauth/additional-providers/hybridauth-xing/Providers/XING.php'
          ),        
      );
      
      public function createAction()
      {
          $oauthApp = $this->get('campaignchain.security.authentication.client.oauth.application');
          $application = $oauthApp->getApplication(self::RESOURCE_OWNER);

          if (!$application) {

              return $oauthApp->newApplicationTpl(self::RESOURCE_OWNER, $this->applicationInfo);
          }

          return $this->render(
              'AcmeChannelXingBundle:Create:index.html.twig',
              array(
                  'page_title' => 'Connect with Xing',
                  'app_id' => $application->getKey(),
              )
          );
      }
      
The *createAction()* method wraps CampaignChain's OAuth module and renders 
a splash page asking the user to connect to the XING account by providing 
credentials and granting permission to CampaignChain to access user data. 
This page is rendered with the view script shown below:

.. code-block:: html+jinja

   # src/Acme/Channel/XingBundle/Resources/views/Create/index.html.twig

  {% extends 'CampaignChainCoreBundle:Base:base.html.twig' %}

  {% block body %}
       <div class="jumbotron">
           <p>Connect to a Xing account by logging in to Xing. The username and password will remain with Xing and will not be stored in this application.</p>
           <p><a class="btn btn-primary btn-lg" role="button" onclick="popupwindow('{{ path('acme_channel_xing_login') }}','',600,600);">Connect with Xing</a></p>
       </div>

   {% endblock %}

Here's what it looks like:

.. image:: /images/developer/cookbook/channel-create.png   
   
Clicking the "Connect now" button in the above view requests a 'login' 
route. Define this route as below:

.. code-block:: yaml

    # src/Acme/Channel/XingBundle/Resources/config/routing.yml
    
    acme_channel_xing_login:
        pattern:  /channel/xing/create/login
        defaults: { _controller: AcmeChannelXingBundle:Xing:login }

Next, write a corresponding controller action to use the credentials 
entered by the user, attempt authentication and if successful, add the 
location to the CampaignChain database for later use.

To simplify this task, CampaignChain provides a Location service and a 
Channel Wizard which together encapsulate most of the functionality you 
will need. The code below illustrates the typical process:

::

  <?php
  // src/Acme/Channel/XingBundle/Controller/XingController.php

  namespace Acme\Channel\XingBundle\Controller;
  use CampaignChain\CoreBundle\Entity\Location;
  use Acme\Location\XingBundle\Entity\XingUser;
  use Symfony\Bundle\FrameworkBundle\Controller\Controller;
  use Symfony\Component\HttpFoundation\Request;
  use Symfony\Component\HttpFoundation\Session\Session;

  class XingController extends Controller
  {

    public function loginAction(Request $request)
    {
        $oauth = $this->get('campaignchain.security.authentication.client.oauth.authentication');
        $status = $oauth->authenticate(self::RESOURCE_OWNER, $this->applicationInfo);
        $profile = $oauth->getProfile();

        if(!$status){
            $this->addFlash(
                'warning',
                'A location has already been connected for this Xing account.'
            );

            return $this->render(
                'AcmeChannelXingBundle:Create:login.html.twig',
                array(
                    'redirect' => $this->generateUrl('campaignchain_core_channel')
                )
            );
        }

        $repository = $this->getDoctrine()->getManager();
        $repository->getConnection()->beginTransaction();

        $wizard = $this->get('campaignchain.core.channel.wizard');
        $wizard->setName($profile->displayName);

        // Get the location module.
        $locationService = $this->get('campaignchain.core.location');
        $locationModule = $locationService->getLocationModule(self::LOCATION_BUNDLE, self::LOCATION_MODULE);

        $location = new Location();
        $location->setIdentifier($profile->identifier);
        $location->setName($profile->displayName);
        $location->setImage($profile->photoURL);
        $location->setLocationModule($locationModule);

        $wizard->addLocation($location->getIdentifier(), $location);

        try {
            $channel = $wizard->persist();
            $wizard->end();

            $oauth->setLocation($channel->getLocations()->first());

            $user = new XingUser();
            $user->setLocation($channel->getLocations()->first());
            $user->setIdentifier($profile->identifier);
            $user->setDisplayName($profile->displayName);
            $user->setFirstName($profile->firstName);
            $user->setLastName($profile->lastName);
            $user->setProfileImageUrl($profile->photoURL);

            if (isset($profile->emailVerified)) {
              $user->setEmail($profile->emailVerified);
            } else {
              $user->setEmail($profile->email);
            }

            $repository->persist($user);
            $repository->flush();

            $repository->getConnection()->commit();

        } catch (\Exception $e) {
            $repository->getConnection()->rollback();
            throw $e;
        }

        $this->addFlash(
            'success',
            'The Xing location <a href="#">'.$profile->displayName.'</a> was connected successfully.'
        );

        return $this->render(
            'AcmeChannelXingBundle:Create:login.html.twig',
            array(
                'redirect' => $this->generateUrl('campaignchain_core_channel')
            )
        );

    }
  }
 
The first few lines of the *loginAction()* action method use CampaignChain's 
OAuth module, which in turn uses HybridAuth, to authenticate against the 
remote service. If authentication is successful, the OAuth object's *getProfile()* 
method returns the profile of the authenticated user. This location now 
needs to be added to CampaignChain's database.

To accomplish this, the action method first creates a new Channel Wizard 
object, which is a convenience object that makes it easy to connect the 
new location to the channel and save it to CampaignChain's database. The 
Channel Wizard is invoked as a Symfony service. The Channel Wizard is also 
assigned a name using its *setName()* method; this could be a fixed name, 
or based on input entered by the user (although you'd need to provide a 
form field in the view to accept this input).

The whole point of logging in is to authorize CampaignChain to connect 
a Location. So, the action method then calls CampaignChain's Location service 
to identify the Location module. The Location module's name and unique module 
identifier play a critical role in helping the Channel Wizard correctly 
identify and store the Location so that CampaignChain can generate routes 
for the Location. 

The method initializes a new Location object using the information from 
the returned user profile, and attaches this Location object to the Channel 
using the Channel Wizard's *addLocation()* method. The information about the 
new Location is saved to the database using the Channel Wizard's *persist()* 
method. 

Since every Location is typically associated with a user profile or activity 
stream, it makes sense to also store additional information about the user 
in the CampaignChain database. The typical properties you'd want to store 
are the user identifier, first name, last name, email address, profile URL 
and profile image URL, plus any properties specific to the channel you're 
connecting. In this example, this information is encapsulated in a XingUser 
entity, with properties and getter/setter methods for the user identifier, 
first name, last name, email address, XING profile URL and XING profile 
image URL. 

The XingUser entity logically belongs in the Location module and can be 
seen below. Entity records are stored in the *acme_location_xing_user* 
table in the CampaignChain database and each record has a 1:1 relationship 
with CampaignChain's core Location entity.

::

 <?php
 // src/Acme/Location/XingBundle/Entity/XingUser.php

  namespace Acme\Location\XingBundle\Entity;

  use Doctrine\ORM\Mapping as ORM;
  use CampaignChain\CoreBundle\Util\ParserUtil;

  /**
   * @ORM\Entity
   * @ORM\Table(name="acme_location_xing_user")
   */
  class XingUser
  {
      /**
       * @ORM\Column(type="integer")
       * @ORM\Id
       * @ORM\GeneratedValue(strategy="AUTO")
       */
      protected $id;
      
      /**
       * @ORM\OneToOne(targetEntity="CampaignChain\CoreBundle\Entity\Location", cascade={"persist"})
       */
      protected $location;
      
      /**
       * @ORM\Column(type="string", length=255, unique=true)
       */
      protected $identifier;
      
      /**
       * @ORM\Column(type="string", length=255)
       */
      protected $displayName;
      
      /**
       * @ORM\Column(type="string", length=255, nullable=true)
       */
      protected $firstName;
      
      /**
       * @ORM\Column(type="string", length=255, nullable=true)
       */
      protected $lastName;

      /**
       * @ORM\Column(type="string", length=255, nullable=true)
       */
      protected $email;
      
      /**
       * @ORM\Column(type="string", length=255, nullable=true)
       */
      protected $profileUrl;
      
      /**
       * @ORM\Column(type="string", length=255, nullable=true)
       */
      protected $profileImageUrl;
       
      /**
       * Get id
       *
       * @return integer
       */
      public function getId()
      {
          return $this->id;
      }
      
      /**
       * Set location
       *
       * @param \CampaignChain\CoreBundle\Entity\Location $location
       * @return User
       */
      public function setLocation(\CampaignChain\CoreBundle\Entity\Location $location = null)
      {
          $this->location = $location;
          return $this;
      }
      
      /**
       * Get location
       *
       * @return \CampaignChain\CoreBundle\Entity\Location
       */
      public function getLocation()
      {
          return $this->location;
      }
          
      /**
       * Set identifier
       *
       * @param string $identifier
       * @return LocationBase
       */
      public function setIdentifier($identifier)
      {
          $this->identifier = $identifier;
          return $this;
      }
      
      /**
       * Get identifier
       *
       * @return string
       */
      public function getIdentifier()
      {
          return $this->identifier;
      }
      
      /**
       * Set displayName
       *
       * @param string $displayName
       * @return User
       */
      public function setDisplayName($displayName)
      {
          $this->displayName = $displayName;
          return $this;
      }
      
      /**
       * Get displayName
       *
       * @return string 
       */
      public function getDisplayName()
      {
          return $this->displayName;
      }
      
      /**
       * Set firstName
       *
       * @param string $firstName
       * @return User
       */
      public function setFirstName($firstName)
      {
          $this->firstName = $firstName;
          return $this;
      }
      
      /**
       * Get firstName
       *
       * @return string 
       */
      public function getFirstName()
      {
          return $this->firstName;
      }
      
      /**
       * Set lastName
       *
       * @param string $lastName
       * @return User
       */
      public function setLastName($lastName)
      {
          $this->lastName = $lastName;
          return $this;
      }
      
      /**
       * Get lastName
       *
       * @return string 
       */
      public function getLastName()
      {
          return $this->lastName;
      }
      
      /**
       * Set email
       *
       * @param string $email
       * @return User
       */
      public function setEmail($email)
      {
          $this->email = $email;
          return $this;
      }
      
      /**
       * Get email
       *
       * @return string 
       */
      public function getEmail()
      {
          return $this->email;
      }
      
      /**
       * Set profileUrl
       *
       * @param string $profileUrl
       * @return User
       */
      public function setProfileUrl($profileUrl)
      {
          $this->profileUrl = ParserUtil::sanitizeUrl($profileUrl);
          return $this;
      }
      
      /**
       * Get profileUrl
       *
       * @return string 
       */
      public function getProfileUrl()
      {
          return $this->profileUrl;
      }
      
      /**
       * Set profileImageUrl
       *
       * @param string $profileImageURL
       * @return User
       */
      public function setProfileImageUrl($profileImageUrl)
      {
          $this->profileImageUrl = $profileImageUrl;
          return $this;
      }
      
      /**
       * Get profileImageUrl
       *
       * @return string
       */
      public function getProfileImageUrl()
      {
          return $this->profileImageUrl;
      }
      
  }
  
.. _Add a channel icon:

3. Add a Channel Icon
~~~~~~~~~~~~~~~~~~~~~

Every Channel module should include a channel icon image, for easy identification 
within the CampaignChain GUI. In most cases, the channel you're trying to connect
to will provide a logo image, so all that's really needed is to resize it to 3 
different sizes (16x16, 24x24 and 32x32 pixels) and save it in PNG format. 

.. note::
   Remember to read the channel's terms of use for its images, ensure that 
   your usage of the image is compliant and provide an image credit, 
   link and/or attribution as needed.

For the XING Channel module created in this tutorial, the 16x16 channel icon 
image should be saved to *your-project/src/Acme/Location/XingBundle/Resources/public/images/icons/16x16/xing.png*. 
Other image sizes should be saved similarly. The name of the image ('xing') 
should match the descriptive string used in the module name ('acme-xing')

At this point, your Channel and Location modules are complete.

Define Activities and Operations
--------------------------------

With the Channel and Location defined, the next step is to define the 
Activities and Operations possible. To keep things simple, we'll assume 
that only a single Activity is required: sharing news on the user's XING 
news stream. This will be accomplished using XING's REST API, which makes 
it possible to add posts to a user's news stream.

.. _Generate Operation and Activity modules:

1. Generate Operation and Activity modules
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The first step here is again to create modules for the Activity and Operation. 
Remember that every Activity must have at least one Operation. In this 
case, since only one Operation is needed, the Activity is equal to the Operation.
This is important to know in advance, as it's critical to proper functioning 
and it's also part of the information requested by the module generator.

Since Activity and Operation modules are linked, it's generally recommended 
that you create the Operation module first and the Activity module later. 
Use the CampaignChain module generator as before, and be aware that you 
will be asked for additional information for Activity and Operation modules, 
as shown below:

.. code-block:: bash

  $ php app/console campaignchain:generate:module
  Module type: Operation
  Vendor name: Acme
  Module name: Xing
  Module name suffix: message 
  Module display name: Post message on XING
  Module description: This module posts a message on XING
  Does the operation own its location?: true 
  Metrics for the operation: Comments, Likes  
  Author name: Acme Inc.
  Author's email address: info@acme.example.com
  Package license: Apache-2.0
  Package description: XING module for CampaignChain
  Package website URL: http://acme.example.com

The new bundle will be created at *your-project/src/Acme/Operation/XingBundle* 
with the name *AcmeOperationXingBundle*.  

Next, create the corresponding Activity module, as below. Note that the module 
name suffix is left empty on purpose for this tutorial.

.. code-block:: bash

  $ php app/console campaignchain:generate:module
  Module type: Activity
  Vendor name: Acme
  Module name: Xing
  Module name suffix:  
  Module display name: Post message on XING
  Module description: This module posts a message on XING
  Does the Activity module execute in a single Channel?: yes
  Channels for the activity: acme/channel-xing/acme-xing
  Hooks for the activity: campaignchain-due, campaignchain-assignee
  Location parameter name: campaignchain.location.acme.xing
  Does the Activity equal an Operation?: true  
  Operation parameter names for the Activity: campaignchain.operation.acme.xing.message  
  Author name: Acme Inc.
  Author's email address: info@acme.example.com
  Package license: Apache-2.0
  Package description: XING module for CampaignChain
  Package website URL: http://acme.example.com

Note that the module and module name suffix used in the Operation module 
should be correctly referenced in the Activity module's Operation parameter 
name.  
  
The new bundle will be created at *your-project/src/AcmeActivity/XingBundle* 
with the name *AcmeActivityXingBundle*.

.. note::
   Most of the code you see in the next few sections is automatically generated 
   for you by the CampaignChain module generator. You only need to copy and 
   paste the parts that are specific to the channel you're trying to 
   connect (in this example, XING).

.. _Understand the API exposed by the channel you're connecting:

2. Understand the XING API
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Once the modules are created, let's look more closely at the message posting 
operation to be implemented. Review the image below, which displays a typical 
item in a XING user's news stream.

.. image:: /images/developer/cookbook/xing-message.png

As you can see, a XING news item is a simple text message. The most efficient 
way to post such a message to a XING user's stream programmatically is 
with the XING API. Using this API involves sending an authenticated POST 
request to the API endpoint https://api.xing.com/v1/users/:id/status_message, 
and transmitting the message in the body of the POST request. The XING 
documentation has `an example and more information`_.

Fortunately, you don't need to worry about the nitty-gritty of creating, 
transmitting and handling POST requests and responses. CampaignChain internally 
uses `Guzzle`_ and so, you can simply invoke Guzzle's *post()* method to 
transmit a POST request and process a POST response. Here's an example of 
how it would work:

::

  <?php
  
    $client = new GuzzleHttp\Client(['base_uri' => 'https://api.xing.com/v1/']);
    $request = $client->post(
        'users/123456/status_message', 
        array(), 
        array('id' => '123456', 'message' => 'Hello world')
    );
    $response = $request->send();

    
Obviously, you still need an input form in CampaignChain for the user to 
enter the message. And, as one of CampaignChain's core capabilities is the 
ability to schedule activities and operations ahead of time, you'll need 
to store newly-created messages in the CampaignChain database, and implement 
a job to transmit them to XING at the appropriate time. The following sections 
will guide you through these tasks.

.. _Create entities and entity managers for your Activities and Operations:

3. Create An Entity and Entity Manager 
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The first step is to create a XingMessage entity representing a XING message, 
and a service manager to work with that entity. A stub entity should have 
been auto-generated for you already at 
*your-project/src/Acme/Operation/XingBundle/Entity/XingMessage.php*. Simply 
update it to reflect the information you wish to save for a message, as below:

::

  <?php

  // src/Acme/Operation/XingBundle/Entity/XingMessage.php

  namespace Acme\Operation\XingBundle\Entity;

  use CampaignChain\CoreBundle\Entity\Meta;
  use Doctrine\ORM\Mapping as ORM;

  /**
   * @ORM\Entity
   * @ORM\Table(name="acme_operation_xing_message")
   */
  class XingMessage extends Meta
  {
      /**
       * @ORM\Column(type="integer")
       * @ORM\Id
       * @ORM\GeneratedValue(strategy="AUTO")
       */
      protected $id;

      /**
       * @ORM\OneToOne(targetEntity="CampaignChain\CoreBundle\Entity\Operation", cascade={"persist"})
       */
      protected $operation;

      /**
       * @ORM\Column(type="text", length=420)
       */
      protected $message;

      /**
       * @ORM\Column(type="text", length=255, nullable=true)
       */
      protected $url;
      
      /**
       * @ORM\Column(type="text", length=255, nullable=true)
       */
      protected $messageId;      
      
      /**
       * Get id
       *
       * @return integer 
       */
      public function getId()
      {
          return $this->id;
      }

      /**
       * Set operation
       *
       * @param \CampaignChain\CoreBundle\Entity\Operation $operation
       * @return Status
       */
      public function setOperation(\CampaignChain\CoreBundle\Entity\Operation $operation = null)
      {
          $this->operation = $operation;

          return $this;
      }

      /**
       * Get operation
       *
       * @return \CampaignChain\CoreBundle\Entity\Operation
       */
      public function getOperation()
      {
          return $this->operation;
      }

      /**
       * Set message
       *
       * @param string $message
       * @return XingMessage
       */
      public function setMessage($message)
      {
          $this->message = $message;

          return $this;
      }

      /**
       * Get message
       *
       * @return string 
       */
      public function getMessage()
      {
          return $this->message;
      }

      /**
       * Set URL
       *
       * @param string $url
       * @return XingMessage
       */
      public function setUrl($url)
      {
          $this->url = $url;

          return $this;
      }

      /**
       * Get URL
       *
       * @return string 
       */
      public function getUrl()
      {
          return $this->url;
      }    
      
      /**
       * Set message id
       *
       * @param string $messageId
       * @return XingMessage
       */
      public function setMessageId($messageId)
      {
          $this->messageId = $messageId;

          return $this;
      }

      /**
       * Get message id
       *
       * @return string 
       */
      public function getMessageId()
      {
          return $this->messageId;
      }      
  }

As you can see, the entity includes properties corresponding to those expected 
by the XING API (in this case, the message text and the unique message 
identifier on XING), as well as some properties needed by CampaignChain.

You will also need an entity service manager, which will retrieve an instance 
of the entity by its identifier. Here's the code, which should be saved to 
*your-project/src/Acme/Operation/XingBundle/EntityService/XingMessage.php*.

::

  <?php

  // src/Acme/Operation/XingBundle/EntityService/XingMessage.php

  namespace Acme\Operation\XingBundle\EntityService;

  use Doctrine\ORM\EntityManager;
  use CampaignChain\CoreBundle\EntityService\OperationServiceInterface;
  use CampaignChain\CoreBundle\Entity\Operation;

  class XingMessage implements OperationServiceInterface
  {
      /**
       * @var EntityManager
       */
      protected $em;
      
      public function __construct(EntityManager $em)
      {
          $this->em = $em;
      }
      
      public function getMessageByOperation($id)
      {
          $message = $this->em
            ->getRepository('AcmeOperationXingBundle:XingMessage')
            ->findOneByOperation($id);

          if (!$message) {
              throw new \Exception(
                  'No message found by operation id '.$id
              );
          }

          return $message;
      }
      
      public function cloneOperation(Operation $oldOperation, Operation $newOperation)
      {
          $message = $this->getMessageByOperation($oldOperation);
          $clonedMessage = clone $message;
          $clonedMessage->setOperation($newOperation);

          $this->em->persist($clonedMessage);
          $this->em->flush();
      }
      
      public function removeOperation($id)
      {
          try {
              $operation = $this->getMessageByOperation($id);

              $this->em->remove($operation);
              $this->em->flush();
          } catch (\Exception $e) {
          }
      }
  }
  
The *getMessageByOperation()* method takes care of retrieving a specific 
message using its unique identifier in the database.

This is also a good point to update the Operation module's list of exposed 
services to include the new entity service manager. To do this, update the 
file at *your-project/src/Acme/Operation/XingBundle/Resources/config/services.yml*
and add the service identifier to it, as shown below. Remember to leave 
the existing auto-generated service identifiers as is.

.. code-block:: yaml

  # src/Acme/Operation/XingBundle/Resources/config/services.yml

  parameters:

  services:
      campaignchain.operation.acme.xing.message:
          class: Acme\Operation\XingBundle\EntityService\XingMessage
          arguments: [ @doctrine.orm.entity_manager ]

        
.. _Create input forms and connect them to your entities:

4. Create an Input Form for Entity Data
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

With the entity created, the next step is to provide an input form that will 
be rendered by the CampaignChain user interface. This form will be used when 
setting up a new XING message, and the fields in the form must therefore 
correspond with the properties of the XingMessage entity.

The easiest way to create the form is by using Symfony's Form component and 
FormBuilder interface. The following code, which should be saved to the auto-generated 
file at *your-project/src/Acme/Operation/XingBundle/Form/Type/XingMessageOperationType.php*,
illustrates how to do this.

::

  <?php

  // src/Acme/Operation/XingBundle/Form/Type/XingMessageOperationType.php

  namespace Acme\Operation\XingBundle\Form\Type;

  use CampaignChain\CoreBundle\Form\Type\OperationType;
  use Symfony\Component\Form\FormBuilderInterface;
  use Symfony\Component\OptionsResolver\OptionsResolver;
  use Symfony\Component\Form\Extension\Core\Type\TextType;

  class XingMessageOperationType extends OperationType
  {
      public function buildForm(FormBuilderInterface $builder, array $options)
      {
          $builder
              ->add('message', TextType::class, [
                  'property_path' => 'message',
                  'label' => 'Message',
                  'attr' => [
                      'placeholder' => 'Add message...',
                      'max_length' => 420
                  ]
              ]);
      }

      public function configureOptions(OptionsResolver $resolver)
      {
          $defaults = [
              'data_class' => 'Acme\Operation\XingBundle\Entity\XingMessage',
          ];

          if ($this->content) {
              $defaults['data'] = $this->content;
          }
          $resolver->setDefaults($defaults);
      }

      public function getBlockPrefix()
      {
          return 'acme_operation_xing_message';
      }
  }

The main work here is done by the *buildForm()* method, which takes care of 
creating the necessary form fields, and the *setDefaultOptions()* method, 
which links the data entered into the form with the XingMessage entity 
created earlier.

Here's an example of what the form looks like when rendered:

.. image:: /images/developer/cookbook/activity-create.png

.. _Create an API client and operation processor:

5. Create an API Client and Operation Processor
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

In the previous steps, you enabled the user to enter details of a new XING 
message into a form and have that data saved to the CampaignChain database. 
The next step is to build an operation processor, which can check periodically for 
scheduled messages, authenticate against the XING API as needed, and post 
those messages to the user's stream.

To accomplish this task, it is necessary to create an HTTP client object 
which will handle authentication between CampaignChain on the one hand, 
and the XING API on the other hand. Since CampaignChain already comes with 
an OAuth client, you can use this client's built-in functionality to take care 
of most of the heavy lifting.

To do this, go back to your Channel module and add the following XingClient 
object to it, at the location *your-project/src/Acme/Channel/XingBundle/REST/XingClient.php*.

::

  <?php

  // src/Acme/Channel/XingBundle/REST/XingClient.php

  namespace Acme\Channel\XingBundle\REST;

  use Symfony\Component\HttpFoundation\Session\Session;
  use Guzzle\Http\Client;
  use Guzzle\Plugin\Oauth\OauthPlugin;
  use Guzzle\Http\Exception\ClientErrorResponseException;
  use Guzzle\Http\Exception\ServerErrorResponseException;
  use Guzzle\Http\Exception\BadResponseException;
  use CampaignChain\Security\Authentication\Client\OAuthBundle\EntityService\ApplicationService;
  use CampaignChain\Security\Authentication\Client\OAuthBundle\EntityService\TokenService;

  class XingClient
  {
      const RESOURCE_OWNER = 'Xing';
      const BASE_URL   = 'https://api.xing.com/v1';

      /**
       * @var ApplicationService
       */
      protected $applicationService;

      /**
       * @var TokenService
       */
      protected $tokenService;

      /**
        * XingClient constructor.
        * @param ApplicationService $applicationService
        * @param TokenService $tokenService
        */
      public function __construct(ApplicationService $applicationService, TokenService $tokenService)
      {
          $this->applicationService = $applicationService;
          $this->tokenService = $tokenService;
      }

      public function connectByActivity($activity)
      {
          return $this->connectByLocation($activity->getLocation());
      }
      
      public function connectByLocation($location)
      {
          $application = $this->applicationService->getApplication(self::RESOURCE_OWNER);
          $token = $this->tokenService->getToken($location);

          return $this->connect($application->getKey(), $application->getSecret(), $token->getAccessToken(), $token->getTokenSecret());
      }

      public function connect($appKey, $appSecret, $accessToken, $tokenSecret)
      {
          try {
              $client = new Client(self::BASE_URL.'/');
              $oauth  = new OauthPlugin(array(
                  'consumer_key'    => $appKey,
                  'consumer_secret' => $appSecret,
                  'token'           => $accessToken,
                  'token_secret'    => $tokenSecret,
              ));

              return $client->addSubscriber($oauth);
          } catch (ClientErrorResponseException $e) {
              $request = $e->getRequest();
              $response = $e->getResponse();
              print_r($request);
              print_r($response);
          } catch (ServerErrorResponseException $e) {
              $request = $e->getRequest();
              $response = $e->getResponse();
              print_r($response);
          } catch (BadResponseException $e) {
              $request = $e->getRequest();
              $response = $e->getResponse();
              print_r($response);
          } catch(Exception $e){
            print_r($e->getMessage());
          }  
      }
  }
  
The two important values set in this client are the constants at the top: 
the RESOURCE_OWNER constant specifies the owning channel, which is then used 
to retrieve the keys and secrets needed for an authenticated API connection, 
and the BASE_URL constant specifies the base URL for all API requests.

You will also need to update the Channel module's list of exposed services 
to include the new client. To do this, update the file at 
*your-project/src/Acme/Channel/XingBundle/Resources/config/services.yml*
with the following information.

.. code-block:: yaml

  # src/Acme/Channel/XingBundle/Resources/config/services.yml

  parameters:

  services:
      acme.channel.xing.rest.client:
          class: Acme\Channel\XingBundle\REST\XingClient
          arguments: ["@campaignchain.security.authentication.client.oauth.application", "@campaignchain.security.authentication.client.oauth.token"]

You'll notice that this client object merely takes care of connecting and 
authenticating against the XING API. It doesn't actually take care of 
creating and sending a POST request to the XING API. That task is handled 
by a separate Job object, which should have been auto-generated within 
your Operation module at *your-project/src/Acme/Operation/XingBundle/Job/XingMessage.php*.

::

  <?php
  
  // src/Acme/Operation/XingBundle/Job/XingMessage
  
  namespace Acme\Operation\XingBundle\Job;

  use CampaignChain\CoreBundle\Entity\Action;
  use Doctrine\ORM\EntityManager;
  use CampaignChain\CoreBundle\Entity\Medium;
  use CampaignChain\CoreBundle\Job\JobActionInterface;
  use Symfony\Component\HttpFoundation\Response;
  use CampaignChain\CoreBundle\EntityService\CTAService;
  use CampaignChain\Security\Authentication\Client\OAuthBundle\EntityService\TokenService;

  class XingMessage implements JobActionInterface
  {
      /**
       * @var EntityManager
       */
      protected $em;

      /**
       * @var TokenService
       */
      protected $tokenService;

      /**
       * @var XingClient
       */
      protected $xingClient;

      public function __construct(EntityManager $em, TokenService $tokenService, XingClient $xingClient)
      {
          $this->em = $em;
          $this->tokenService = $tokenService;
          $this->xingClient = $xingClient;
      }

      public function execute($operationId)
      {
          $message = $this->em
              ->getRepository('AcmeOperationXingBundle:XingMessage')
              ->findOneByOperation($operationId);

          if (!$message) {
              throw new \Exception('No message found for an operation with ID: '.$operationId);
          }

          $ctaService = $this->container->get('campaignchain.core.cta');
          $message->setMessage(
              $ctaService->processCTAs($message->getMessage(), $message->getOperation(), CTAService::FORMAT_TXT)->getContent()
          );
          
          $activity = $message->getOperation()->getActivity();
          $identifier = $activity->getLocation()->getIdentifier();
          $token = $this->tokenService->getToken($activity->getLocation());
          
          $connection = $this->xingClient->connectByActivity($message->getOperation()->getActivity());
          
          $request = $connection->post('users/' . $identifier . '/status_message', array(), array('id' => $identifier, 'message' => $message->getMessage()));
          $response = $request->send();
          $messageEndpoint = $response->getHeader('location');
          $messageId = basename($messageEndpoint);
          $messageUrl = 'https://www.xing.com/feedy/stories/' . strtok($messageId, '_');
          $message->setUrl($messageUrl);
          $message->setMessageId($messageId);

          $message->getOperation()->setStatus(Action::STATUS_CLOSED);
          $location = $message->getOperation()->getLocations()[0];
          $location->setIdentifier($messageId);
          $location->setUrl($messageUrl);
          $location->setName($message->getOperation()->getName());
          $location->setStatus(Medium::STATUS_ACTIVE);
          
          $this->em->flush();

          $this->message = 'The message "'.$message->getMessage().'" with the ID "'.$messageId.'" has been posted on XING. See it on XING: <a href="'.$messageUrl.'">'.$messageUrl.'</a>';

          return self::STATUS_OK;
      }
  }
  
A Job object is always part of an Operation module and it is called as necessary 
to perform the corresponding operation. It should implement the JobActionInterface, 
which mandates an *execute()* method which is called when the job is executed. 

If you look into the *execute()* method above, you'll see that it begins by 
retrieving the required message from the CampaignChain database (using the 
message identifier). It then uses CampaignChain's CTA service and 
*processCTAs()* method to inspect all URLs in the message body and replace 
those URLs that match a Location with short URLs for tracking.

The next step is to invoke the XingClient created earlier from the service 
manager and uses the client to authenticate against the XING API. The method 
uses the client's inherited *post()* method to transmit a POST request to the 
API endpoint https://api.xing.com/v1/users/ID/status_message containing the 
user's identifier on XING and the message content. If successful, the response 
will contain a Location header containing the URL to the posted message. 
It's now easy enough to extract the message identifier from this and create 
a new Location record pointing to it in the CampaignChain database. This 
Location can later be used in CampaignChain's Call-to-Action tracking. 

At the same time, a new XingMessage record is also created to store the 
message URL and unique message identifier on XING. This message identifier 
is particularly important, as it will later be used to collect statistics 
about the number of likes and comments received on the message.

The final steps are to update the status of the operation in the CampaignChain 
database and present a success message to the user.

You also need to update the Activity module's list of exposed services to include 
the new job. To do this, update the file at 
*your-project/src/Acme/Activity/XingBundle/Resources/config/services.yml*
so it now looks like the following.

.. code-block:: yaml

  # src/Acme/Activity/XingBundle/Resources/config/services.yml
  
  parameters:
  # Parameters for the CampaignChain Activity modules in this Symfony bundle
      campaignchain.activity.acme.xing:
          bundle_name: "acme/activity-xing"
          module_identifier: "acme-xing"
          location: %campaignchain.location.acme.xing%
          equals_operation: true
          operations:
              - %campaignchain.operation.acme.xing.message%
          handler: "campaignchain.activity.controller.handler.acme.xing"

  services:
      # The Symfony service evoking the default controller of the CampaignChain
      # core package
      campaignchain.activity.controller.acme.xing:
          class: CampaignChain\CoreBundle\Controller\Module\ActivityModuleController
          calls:
              - [setContainer, ["@service_container"]]
              - [setParameters, ["%campaignchain.activity.acme.xing%"]]
      # The CampaignChain controller handler where the Activity's GUI and data
      # is being processed.
      campaignchain.activity.controller.handler.acme.xing:
        class: Acme\Activity\XingBundle\Controller\XingHandler
        arguments:
            - "@doctrine.orm.entity_manager"
            - "@session"
            - "@templating"
            - "@campaignchain.operation.acme.xing.message"
            - "@campaignchain.job.operation.acme.xing.message"

            
.. _Define an Activity handler:

6. Define an Activity Handler
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The Activity module specifies the routes for creating and 
editing Operations. This implies that the Activity should define 
four routes:

* A route to create a new Activity ('new')
* A route to edit an existing Activity ('edit')
* A route to display the details of an existing Activity ('read')
* A route to edit an existing Activity in the campaign timeline's 
  pop-up/lightbox view ('edit_modal')
* A route for the submit action of the pop-up/lightbox view in the 
  campaign timeline ('edit_api')

These routes are automatically generated for you in the Activity module's 
*campaignchain.yml* file, as shown below:

.. code-block:: yaml

  # src/Acme/Activity/XingBundle/campaignchain.yml

  modules:
      campaignchain-xing:
          display_name: Post message on Xing
          description: This module posts a message on Xing
          channels: 
              - acme/channel-xing/acme-xing
          routes: 
              new: acme_activity_xing_new
              edit: acme_activity_xing_edit
              edit_modal: acme_activity_xing_edit_modal
              edit_api: acme_activity_xing_edit_api
              read: acme_activity_xing_read
          hooks:
              default:
                  campaignchain-due: true
                  campaignchain-assignee: true  
                  
The corresponding controller and action names are also auto-generated in 
the Activity module's *routing.yml* file:

.. code-block:: yaml

  # src/Acme/Activity/XingBundle/campaignchain.yml
  
  acme_activity_xing_new:
      pattern: /activity/xing/new
      defaults: { _controller: campaignchain.activity.controller.acme.xing:newAction }

  acme_activity_xing_edit:
      pattern: /activity/xing/{id}/edit
      defaults: { _controller: campaignchain.activity.controller.acme.xing:editAction }

  acme_activity_xing_edit_modal:
      pattern: /modal/activity/xing/{id}/edit
      defaults: { _controller: campaignchain.activity.controller.acme.xing:editModalAction }

  acme_activity_xing_edit_api:
      pattern: /api/private/activity/xing/byactivity/{id}/edit
      defaults: { _controller: campaignchain.activity.controller.acme.xing:editApiAction }
      options:
          expose: true
      
  acme_activity_xing_read:
      pattern: /activity/xing/{id}
      defaults: { _controller: campaignchain.activity.controller.acme.xing:readAction }


Normally, you'd need to create views and controllers for the routes above. 
However, CampaignChain offers you a simpler approach: an ActivityHandler 
which contains methods to retrieve, create and process the data of an Activity. 
A stub ActivityHandler will already be produced for you by the CampaignChain 
module generator; all you need to do is fill out the stub methods with the 
appropriate code for your module. 

Here's the code for the XingHandler:

::

  <?php
  
  // src/Acme/Activity/XingBundle/Controller/XingHandler
  
  namespace Acme\Activity\XingBundle\Controller;

  use CampaignChain\CoreBundle\Controller\Module\AbstractActivityHandler;
  use Symfony\Component\Form\Form;
  use CampaignChain\CoreBundle\Entity\Location;
  use CampaignChain\CoreBundle\Entity\Campaign;
  use CampaignChain\CoreBundle\Entity\Activity;
  use CampaignChain\CoreBundle\Entity\Operation;
  use Doctrine\ORM\EntityManager;
  use Symfony\Bundle\TwigBundle\TwigEngine;
  use Symfony\Component\HttpFoundation\Session\Session;

  use Acme\Operation\XingBundle\Entity\XingMessage;
  use Acme\Operation\XingBundle\EntityService\XingMessage as XingMessageService;
  use Acme\Operation\XingBundle\Job\XingMessage as XingMessageJob;

  /**
   * Class XingHandler
   * @package Acme\Activity\XingBundle\Controller\Module
   */
  class XingHandler extends AbstractActivityHandler
  {
      protected $em;
      protected $session;
      protected $templating;
      protected $contentService;
      protected $job;
      private $message;

      public function __construct(
          EntityManager $em,
          Session $session,
          TwigEngine $templating,
          XingMessageService $contentService,
          XingMessageJob $job
      )
      {
          $this->em = $em;
          $this->session = $session;
          $this->templating = $templating;
          $this->contentService = $contentService;
          $this->job = $job;
      }

      /**
       * When a new Activity is being created, this handler method will be called
       * to retrieve a new Content object for the Activity.
       *
       * Called in these views:
       * - new
       *
       * @param Location $location
       * @param Campaign $campaign
       * @return null
       */
      public function createContent(Location $location = null, Campaign $campaign = null)
      {
          return null;
      }

      /**
       * Overwrite this method to return an existing Activity Content object which
       * would be displayed in a view.
       *
       * Called in these views:
       * - edit
       * - editModal
       * - read
       *
       * @param Location $location
       * @param Operation $operation
       * @return null
       */
      public function getContent(Location $location, Operation $operation)
      {
          return $this->contentService->getMessageByOperation($operation);
      }

      /**
       * Implement this method to change the data of an Activity as per the form
       * data that has been posted in a view.
       *
       * Called in these views:
       * - new
       *
       * @param Activity $activity
       * @param $data Form submit data of the Activity.
       * @return Activity
       */
      public function processActivity(Activity $activity, $data)
      {
          return $activity;
      }

      /**
       * Modifies the Location of the Activity.
       *
       * Called in these views:
       * - new
       *
       * @param Location $location The Activity's Location.
       * @return Location
       */
      public function processActivityLocation(Location $location)
      {
          return $location;
      }

      /**
       * After a new Activity was created, this method makes it possible to alter
       * the data of the Content's Location (not the Activity's Location!) as per
       * the data provided for the Content.
       *
       * Called in these views:
       * - new
       *
       * @param Location $location Location of the Content.
       * @param $data Form submit data of the Content.
       * @return Location
       */
      public function processContentLocation(Location $location, $data)
      {
          return $location;
      }

      /**
       * Create or modify the Content object from the form data.
       *
       * Called in these views:
       * - new
       * - editApi
       *
       * @param Operation $operation
       * @param $data Form submit data of the Content.
       * @return mixed
       */
      public function processContent(Operation $operation, $data)
      {
          try {
              if(is_array($data)) {
                  $message = $this->contentService->getMessageByOperation($operation);
                  $message->setMessage($data['message']);
              } else {
                  $message = $data;            
              }
          } catch (\Exception $e){
              // message has not been created yet, so do it from the form data.
              $message = $data;
          }
          return $message;
      }

      /**
      * Define custom template rendering options for the new view in this method
      * as an array. Here's a sample of such an array:
      *
      * array(
      *     'template' => 'foo_template::edit.html.twig',
      *     'vars' => array(
      *         'foo1' => $bar1,
      *         'foo2' => $bar2
      *         )
      *     );
      *
      * Called in these views:
      * - new
      *
      * @param Operation $operation
      * @return null
      */
      public function getNewRenderOptions(Operation $operation = null)
      {
          return null;
      }

      /**
       * Overwrite this method to define how the Content is supposed to be
       * displayed.
       *
       * Called in these views:
       * - read
       *
       * @param Operation $operation
       * @return mixed
       */
      public function readAction(Operation $operation)
      {
          $message = $this->contentService->getMessageByOperation($operation);

          return $this->templating->renderResponse(
              'CampaignChainOperationXingBundle::read_message.html.twig',
              array(
                  'page_title' => $operation->getActivity()->getName(),
                  'operation' => $operation,
                  'location' => $operation->getActivity()->getLocation(),
                  'activity' => $operation->getActivity(),
                  'message' => $message,
                  'show_date' => true,
              ));
      }

      /**
       * The Activity controller calls this method after the form was submitted
       * and the new activity was persisted.
       *
       * @param Activity $activity
       * @param $data
       */
      public function postFormSubmitNewEvent(Activity $activity, $data)
      {
      }

      /**
       * This event is being called after the new Activity and its related
       * content was persisted.
       *
       * Called in these views:
       * - new
       *
       * @param Operation $operation
       * @param Form $form
       * @param $content The Activity's content object.
       * @return null
       */
      public function postPersistNewEvent(Operation $operation, Form $form, $content = null)
      {
          $this->publishNow($operation, $form, $content);
          $this->em->persist($content);
          $this->em->flush();
      }

      /**
       * This event is being called before the edit form data has been submitted.
       *
       * Called in these views:
       * - edit
       *
       * @param Operation $operation
       * @return null
       */
      public function preFormSubmitEditEvent(Operation $operation)
      {
          return null;
      }

      /**
       * This event is being called after the edited Activity and its related
       * content was persisted.
       *
       * Called in these views:
       * - edit
       *
       * @param Operation $operation
       * @param Form $form
       * @param $content The Activity's content object.
       * @return null
       */
      public function postPersistEditEvent(Operation $operation, Form $form, $content = null)
      {
          $this->publishNow($operation, $form, $content);
      }

      /**
       * Define custom template rendering options for the edit view in this method
       * as an array. Here's a sample of such an array:
       *
       * array(
       *     'template' => 'foo_template::edit.html.twig',
       *     'vars' => array(
       *         'foo1' => $bar1,
       *         'foo2' => $bar2
       *         )
       *     );
       *
       * Called in these views:
       * - edit
       *
       * @param Operation $operation
       * @return null
       */
      public function getEditRenderOptions(Operation $operation)
      {
          return null;
      }

      /**
       * This event is being called before the editModal form data has been
       * submitted.
       *
       * Called in these views:
       * - editModal
       *
       * @param Operation $operation
       * @return null
       */
      public function preFormSubmitEditModalEvent(Operation $operation)
      {
          return null;
      }

      /**
       * Define custom template rendering options for editModal view as array.
       *
       * Called in these views:
       * - editModal
       *
       * @see AbstractActivityHandler::getEditRenderOptions()
       * @param Operation $operation
       * @return null
       */
      public function getEditModalRenderOptions(Operation $operation)
      {
          return null;
      }

      /**
       * Let's a handler implementation define whether the Content should be
       * displayed or processed in a specific view or not.
       *
       * Called in these views:
       * - new
       * - edit
       * - editModal
       * - editApi
       *
       * @param $view
       * @return bool
       */
      public function hasContent($view)
      {
          return true;
      }
      
      private function publishNow(Operation $operation, Form $form)
      {
          if (!$form->get('campaignchain_hook_campaignchain_due')->has('execution_choice') || $form->get('campaignchain_hook_campaignchain_due')->get('execution_choice')->getData() != 'now') {
              return false;
          }

          $this->job->execute($operation->getId());
          $content = $this->contentService->getMessageByOperation($operation);
          $this->session->getFlashBag()->add(
              'success',
              'The message was published.'
          );

          return true;
      }
  }
  
The ActivityHandler includes a number of methods, designed to let you 
customize the handling of key events in the CampaignChain workflow. You'll 
find an explanation in the comments above each method, but let's quickly 
look through the key methods here:

* The constructor injects the key dependencies needed for the handler, 
  including the entity service manager and the job processor.

* The *getContent()* method returns an existing XingMessage entity, for 
  use in an edit or display view.

* The *processContent()* method processes the input submitted in the Operation 
  form and creates a new XingMessage entity. It is also invoked to process 
  modifications to an existing XingMessage entity.

* The *readAction()* method retrieves an existing XingMessage entity and 
  sets template variables from its properties for display.

* The *postPersistNewEvent()* and *postPersistEditEvent()* methods are 
  called after a XingMessage entity is saved to the database. In this example, 
  both methods invoke the *publishNow()* method. 

* The *publishNow()* method checks when the Activity is scheduled for and, 
  if set to "now", retrieves the job via the service manager and invokes its 
  *execute()* method to post the message to the XING API.

.. note::
   The Activity and Operation modules use CampaignChain's base views, and 
   it is not necessary to create new views unless you specifically wish 
   to override the base views.

.. _Collect metrics and create a report processor:

7. Collect Metrics and Create a Report Processor
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Most online channels expose an API to collect metrics on posted data, such 
as the number of favorites, retweets, likes or comments. One of CampaignChain's 
key features is the ability to aggregate this data and generate reports to 
help end-users evaluate the success of a campaign.

To do this, it is necessary to define a second Job, this one responsible 
for periodically connecting to the service's API, collecting metrics and 
saving them to the CampaignChain database. These metrics are then used to 
generate reports through the CampaignChain interface.

The CampaignChain module generator will have got you started by creating a 
stub Job for this purpose within your Operation module, at *your-project/src/Acme/Operation/XingBundle/Job/XingMessageReport.php*. 
You'll notice that this stub file already includes variables for the two 
metrics, likes and comments, which you specified in Step 1 when generating 
the Operation module.

Update this file with the following code:

::

  <?php

  // src/Acme/Operation/XingBundle/Job/XingMessageReport.php

  namespace Acme\Operation\XingBundle\Job;

  use CampaignChain\CoreBundle\Entity\SchedulerReportOperation;
  use CampaignChain\CoreBundle\Job\JobReportInterface;
  use Doctrine\ORM\EntityManager;

  class XingMessageReport implements JobReportInterface
  {
      const OPERATION_BUNDLE_NAME = 'acme/operation-xing';
      const METRIC_LIKES    = 'Likes';
      const METRIC_COMMENTS = 'Comments';

      protected $em;
      protected $container;
      protected $message;
      protected $operation;

      public function __construct(EntityManager $em, $container)
      {
          $this->em = $em;
          $this->container = $container;
      }

      public function getMessage(){
          return $this->message;
      }
      
      public function schedule($operation, $facts = null)
      {
          $scheduler = new SchedulerReportOperation();
          $scheduler->setOperation($operation);
          $scheduler->setInterval('1 hour');
          $scheduler->setEndAction($operation->getActivity()->getCampaign());
          $this->em->persist($scheduler);

          $facts[self::METRIC_LIKES] = 0;
          $facts[self::METRIC_COMMENTS] = 0;

          $factService = $this->container->get('campaignchain.core.fact');
          $factService->addFacts('activity', self::OPERATION_BUNDLE_NAME, $operation, $facts);
      }

      public function execute($operationId)
      {
          $operationService = $this->container->get('campaignchain.core.operation');
          $operation = $operationService->getOperation($operationId);

          $message = $this->em
                          ->getRepository('AcmeOperationXingBundle:XingMessage')
                          ->findOneByOperation($operationId);

          if (!$message) {
              throw new \Exception('No message found for an operation with ID: '.$operationId);
          }

          $activity = $message->getOperation()->getActivity();
          $messageId = $message->getMessageId();

          $client = $this->container->get('acme.channel.xing.rest.client');
          $connection = $client->connectByActivity($activity);
          
          $request = $connection->get('activities/' . $messageId, array());
          $response = $request->send()->json();
          
          if(!count($response)){
              $likes = 0;
              $comments = 0;
          } else {
              $likes = $response['activities'][0]['likes']['amount'];
              $comments = $response['activities'][0]['comments']['amount'];
          }

          // Add report data.
          $facts[self::METRIC_LIKES] = $likes;
          $facts[self::METRIC_COMMENTS] = $comments;

          $factService = $this->container->get('campaignchain.core.fact');
          $factService->addFacts('activity', self::OPERATION_BUNDLE_NAME, $operation, $facts);

          $this->message = 'Added to report: likes = '.$likes.', comments = '.$comments.'.';

          return self::STATUS_OK;
      }

  }

If you look into the *execute()* method above, you'll see that it begins 
by retrieving the required message from the CampaignChain database (using 
the message identifier). It then uses the message object's *getMessageId()* 
method to retrieve the unique identifier for that message on XING.

Next, it invokes the XingClient created earlier from the service manager 
and uses the client to authenticate against the XING API.

It then uses the client's inherited *get()* method to transmit 
a GET request to the API endpoint https://api.xing.com/v1/activities/ID, 
passing the message identifier to XING. If successful, the response will 
include complete details for the specified message, including the number 
of likes and comments it received. It's now easy enough to extract these 
metrics from the response and save them to the CampaignChain database using 
the Fact service. The XING documentation explains `this API method in more 
detail`_.

The *execute()* method does the work of collecting data from the XING API 
and saving it to the CampaignChain database...but how is it invoked? That's 
where the *schedule()* method comes in � it creates a new SchedulerReportOperation 
that runs periodically for a specified operation. In this case, the scheduler 
is configured to collect data every hour, and run for as long as the campaign 
associated with the operation.

Since the scheduler is associated with an Operation, it makes sense to 
invoke the *schedule()* method when the operation is created. So, update 
the *your-project/src/Acme/Operation/XingBundle/Job/XingMessage.php* file 
and add the lines below to its *execute()* method, to be executed after 
the message is successfully posted:

::

  <?php

    // src/Acme/Operation/XingBundle/Job/XingMessage
  
    public function execute($operationId)
    {
        // ... snip
        $location->setStatus(Medium::STATUS_ACTIVE);

        // schedule data collection for report
        $report = $this->container->get('campaignchain.job.report.acme.xing.message');
        $report->schedule($message->getOperation());  
      
        $this->em->flush();
        // ... snip
    }

Conclusion
------------

At this point, your modules are all complete. Once you add your modules 
to CampaignChain through the module installer, or reset your system to 
automatically register them, you should be able to connect to a new XING 
location and begin posting news to it. Try it out for yourself and see 
how easy it is!


.. _XING: http://www.xing.com
.. _Symfony environment: http://symfony.com/doc/current/book/installation.html
.. _Learn more about the API: https://dev.xing.com/docs
.. _Register your application: https://dev.xing.com/applications/dashboard
.. _an example and more information: https://dev.xing.com/docs/post/users/:id/status_message
.. _this API method in more detail: https://dev.xing.com/docs/get/activities/:id
.. _Guzzle: http://docs.guzzlephp.org/en/latest/quickstart.html
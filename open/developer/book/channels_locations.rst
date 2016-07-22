Channel and Location Modules
============================

This document provides an overview of concepts that developers should 
know when developing Channel and Location modules.

.. note::
   Every Channel must include at least one Location.

Naming Conventions (Channel)
-----------------------------
*composer.json*

* The *name* parameter should be of the form 
  [application name or vendor name]/channel-[channel name].
  
  *Example: campaignchain/channel-twitter*

* The *type* parameter should be 'campaignchain-channel'.

*campaignchain.yml*

* The name of a Channel module should follow the convention 
  [application name or vendor name]-[channel name]. 
  
  *Example: campaignchain-twitter*

Naming Conventions (Location)
-----------------------------
*composer.json*

* The *name* parameter should be of the form 
  [application name or vendor name]/location-[channel name]-[bundle purpose]. 
  
  *Example: campaignchain/location-twitter-status-update*

* The *type* parameter should be 'campaignchain-location'.

*campaignchain.yml*

* The name of a Location module should follow the convention 
  [application name or vendor name]-[channel name]-[location descriptor]. 
  
  *Example: campaignchain-twitter-user*

Wizards and Routes
------------------
CampaignChain provides a set of "wizards" that ease integration of your module
into the CampaignChain GUI. The Channel Wizard takes care of redirecting the
client browser to the appropriate routes when creating or editing a channel 
and/or location.

Channel and Location module developers should use the Channel Wizard as a 
convenient way to attach and persist a new location for a channel. The Channel 
Wizard can be invoked from within a controller using the service identifier 
'campaignchain.core.channel.wizard' as shown below.

::

 <?php
 // invoke and use channel wizard
 $wizard = $this->get('campaignchain.core.channel.wizard');
 $wizard->setName($profile->displayName);
 $wizard->addLocation($location->getIdentifier(), $location);
 $channel = $wizard->persist();
 $wizard->end();

The route used by the Channel Wizard is obtained from the module configuration 
in the Channel bundle's *campaignchain.yml* file:

.. code-block:: yaml

 modules:
    campaignchain-linkedin:
        display_name: LinkedIn
        routes:
            new: campaignchain_channel_linkedin_create

Location Module and Service
---------------------------
The Channel Wizard's *addLocation()* method should be passed a Location 
object representing the location to be added to the channel. CampaignChain's
Location service can be used to retrieve the correct Location module, 
using the Location bundle name and Location module identifier. The 
location service is available using the identifier 'campaignchain.core.location'.

::

 <?php
 $locationService = $this->get('campaignchain.core.location');
 $locationModule = $locationService->getLocationModule(
   'campaignchain/location-linkedin', 'campaignchain-linkedin-user');

In this example, the Location service finds the Location module named 
'campaignchain-linkedin-user' in the bundle named 'campaignchain/location-linkedin'.

Channel Authentication
----------------------
CampaignChain provides an OAuthBundle (based on HybridAuth) which can be used
for OAuth-based authentication with online channels. The client can be 
accessed as a Symfony service using the service identifier 'campaignchain.security.authentication.client.oauth.application'.

::

 <?php
 $oauthApp = $this->get(
   'campaignchain.security.authentication.client.oauth.application');
 $application = $oauthApp->getApplication(self::RESOURCE_OWNER);

 if(!$application){
    return $oauthApp->newApplicationTpl(self::RESOURCE_OWNER, 
      $this->applicationInfo);
 }
 else {
    return $this->render(
        'CampaignChainChannelLinkedInBundle:Create:index.html.twig',
        array(
            'page_title' => 'Connect with LinkedIn',
            'app_id' => $application->getKey(),
        )
    );
 }               

The client's *getApplication()* method retrieves any existing channel 
credentials (that were previously configured) from the CampaignChain database.
In case no such credentials exist (such as the first time a location is 
created), the *getApplicationTpl()* method generates a Web form for the 
user to input the required data.

CampaignChain also provides an OAuth authentication client via the 'campaignchain.security.authentication.client.oauth.authentication'
identifier. The client's *authenticate()* method can be used to perform 
authentication against the remote service.

::

 <?php
 $oauth = $this->get(
   'campaignchain.security.authentication.client.oauth.authentication');
 $status = $oauth->authenticate(self::RESOURCE_OWNER, 
   $this->applicationInfo);

.. note::
   CampaignChain's OAuthBundle is an optional bundle to ease authentication with
   third-party services. Developers are free to implement their own authentication 
   client, or use third-party clients as needed.

Channel Icon
------------
Each Channel module must provide a channel icon image in PNG format with 
size 16x16 pixels. The image file must reside in the *your-project/src/your-bundle-namespace/Resources/public/images/icons/16x16/* 
folder of the bundle and the image's file name should match the descriptive 
string used at the end of the bundle name. 

*Example: The bundle named 'campaignchain/channel-google' would have its icon
reside at your-project/src/Acme/CampaignChain/Channel/GoogleBundle/Resources/public/images/icons/16x16/google.png.*


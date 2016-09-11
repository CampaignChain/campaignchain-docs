CampaignChain Facebook
======================

This documentation covers the standard Facebook functionality available by
default in the CampaignChain Community Edition.

Features
--------

- Connect a Facebook user or page stream to CampaignChain with username and
  password
- Assign a Facebook message to a campaign
- Include 1 picture in the Facebook message
- Schedule a message to automatically post it on Facebook at a given date and
  time
- Assign a responsible person to a Facebook message
- Once a Facebook update was posted, regularly collect statistical data about
  likes and comments

Packages
--------

The standard Facebook functionality is being provided by CampaignChain, Inc.
through these packages:

- `campaignchain/channel-facebook`_
- `campaignchain/location-facebook`_
- `campaignchain/activity-facebook`_
- `campaignchain/operation-facebook`_

Although these modules are based on `Symfony bundles`_, they do not work
independently of CampaignChain.

Installation
------------

The above modules are included in the Community Edition by default.

Configuration
-------------

.. _facebook-oauth-app-configuration:

Before you can post on Facebook from within CampaignChain, an OAuth app must be
created in Facebook:

#. Go to https://developers.facebook.com/apps and create a new application by
   clicking *Create New App*.
#. Fill out any required fields such as the application name and description.
#. Put your website domain in the *Site Url* field.
#. Provide the host name of your CampaignChain instance as the Callback URL
   (e.g. http://mydomain.com). Make sure that you specify the correct scheme
   (`http` or `https`).
#. The Callback URL's parts must be identical with the
   `router.request_context.host` and `router.request_context.scheme` parameters
   defined in the `app/config/parameters.yml` configuration file.
#. Once you have registered the app, `connect to a location`_ while choosing
   Facebook as the Channel.
#. When the *Provide Application Credentials* screen comes up, go back to
   https://developers.facebook.com/apps, select your app and visit the
   *Settings* page to copy and paste the *App ID* and the *App Secret* and
   insert it in the *Provide Application Credentials* form.

.. note::

    Should you want CampaignChain to post to Facebook streams which are not
    owned by the same Facebook account which owns your OAuth App, then you must
    get your OAuth App approved by Facebook. To do so, click on *App Review*
    on the left menu of your Facebook OAuth App.

Issues
------

Please post reports, questions, suggestions, etc. at
https://github.com/CampaignChain/campaignchain/issues.


.. _campaignchain/channel-facebook: https://github.com/CampaignChain/channel-facebook
.. _campaignchain/location-facebook: https://github.com/CampaignChain/location-facebook
.. _campaignchain/activity-facebook: https://github.com/CampaignChain/activity-facebook
.. _campaignchain/operation-facebook: https://github.com/CampaignChain/operation-facebook
.. _Symfony bundles: http://symfony.com/doc/current/bundles.html
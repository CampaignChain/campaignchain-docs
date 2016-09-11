CampaignChain Linkedin
======================

This documentation covers the standard `Linkedin`_ functionality available by
default in the CampaignChain Community Edition.

Features
--------

- Connect a Linkedin stream to CampaignChain with username and password
- Assign a Linkedin message to a campaign
- Include up to 4 pictures in a Tweet
- Schedule a Tweet to automatically post it on Linkedin at a given date and time
- Assign a responsible person to a Tweet
- Once a Tweet was posted, regularly collect statistical data about likes
  and re-tweets

Packages
--------

The standard Linkedin functionality is being provided by CampaignChain, Inc.
through these packages:

- `campaignchain/channel-linkedin`_
- `campaignchain/location-linkedin`_
- `campaignchain/activity-linkedin`_
- `campaignchain/operation-linkedin`_

Although these modules are based on `Symfony bundles`_, they do not work
independently of CampaignChain.

Installation
------------

The above modules are included in the Community Edition by default.

Configuration
-------------

.. _linkedin-oauth-app-configuration:

Before you can post on Linkedin from within CampaignChain, an OAuth app must be
created in Linkedin:

#. Go to https://dev.linkedin.com/apps and create a new application.
#. Fill out any required fields such as the application name and description.
#. Put your website domain in the Website field.
#. Provide the host name of your CampaignChain instance as the Callback URL
   (e.g. http://mydomain.com). Make sure that you specify the correct scheme
   (`http` or `https`).
#. The Callback URL's parts must be identical with the
   `router.request_context.host` and `router.request_context.scheme` parameters
   defined in the `app/config/parameters.yml` configuration file.
#. Once you have registered the app, :ref:`connect to a Location <create-new-oauth-apps>`
   choosing Linkedin as the Channel.
#. When the *Provide Application Credentials* screen comes up, go back to
   https://dev.linkedin.com/apps, select your app and visit the *Keys and
   Access Tokens* tab to copy and paste the *Consumer Key* and the *Consumer
   Secret* and insert it in the *Provide Application Credentials* form.

Issues
------

Please post reports, questions, suggestions, etc. at
https://github.com/CampaignChain/campaignchain/issues.

.. _Linkedin: https://www.linkedin.com
.. _campaignchain/channel-linkedin: https://github.com/CampaignChain/channel-linkedin
.. _campaignchain/location-linkedin: https://github.com/CampaignChain/location-linkedin
.. _campaignchain/activity-linkedin: https://github.com/CampaignChain/activity-linkedin
.. _campaignchain/operation-linkedin: https://github.com/CampaignChain/operation-linkedin
.. _Symfony bundles: http://symfony.com/doc/current/bundles.html
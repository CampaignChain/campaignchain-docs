CampaignChain GoToWebinar
=====================

This documentation covers the standard `GoToWebinar`_ functionality available by
default in the CampaignChain Community Edition.

Features
--------

- Connect a GoToWebinar account to CampaignChain with username and password
- Assign a GoToWebinar Webinar to a campaign within CampaignChain
- (Re-)schedule a Webinar at a given date and time
- Within CampaignChain, assign a responsible person to a Webinar
- Collect statistics about registrations prior to a Webinar and afterwards the
  number of participants

Packages
--------

The standard GoToWebinar functionality is being provided by CampaignChain, Inc.
through these packages:

- `campaignchain/channel-citrix`_
- `campaignchain/location-citrix`_
- `campaignchain/activity-gotowebinar`_
- `campaignchain/operation-gotowebinar`_

Although these modules are based on `Symfony bundles`_, they do not work
independently of CampaignChain.

Installation
------------

The above modules are included in the Community Edition by default.

Configuration
-------------

.. _gotowebinar-oauth-app-configuration:

Before you can manage a GoToWebinar Webinar from within CampaignChain, an OAuth
app must be created in Citrix (the company behind GoToWebinar):

#. Go to https://developer.citrixonline.com/user/me/apps and add a new app.
#. Fill out any required fields such as the application name and description and
   select *GoToWebinar* as the *Product API*.
#. Provide the host name of your CampaignChain instance as the *Application URL*
   (e.g. http://mydomain.com). Make sure that you specify the correct scheme
   (`http` or `https`).
#. The Callback URL's parts must be identical with the
   `router.request_context.host` and `router.request_context.scheme` parameters
   defined in the `app/config/parameters.yml` configuration file.
#. Once you have added the app, :ref:`connect to a Location <create-new-oauth-apps>`
   choosing GoToWebinar as the Channel.
#. When the *Provide Application Credentials* screen comes up, go back to
   https://developer.citrixonline.com/user/me/apps, select your app and visit
   the *Keys* tab to copy and paste the *Consumer Key* and the *Consumer
   Secret* and insert it in the *Provide Application Credentials* form.

.. note::

    If you already have an account for http://developer.citrixonline.com, you
    would still have to create a new separate account for
    https://www.gotomeeting.com/webinar should you not already have one.

Issues
------

Please post reports, questions, suggestions, etc. at
https://github.com/CampaignChain/campaignchain/issues.

.. _GoToWebinar: https://www.gotomeeting.com/webinar
.. _campaignchain/channel-citrix: https://github.com/CampaignChain/channel-citrix
.. _campaignchain/location-citrix: https://github.com/CampaignChain/location-citrix
.. _campaignchain/activity-gotowebinar: https://github.com/CampaignChain/activity-gotowebinar
.. _campaignchain/operation-gotowebinar: https://github.com/CampaignChain/operation-gotowebinar
.. _Symfony bundles: http://symfony.com/doc/current/bundles.html
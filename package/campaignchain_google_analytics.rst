CampaignChain Google Analytics
==============================

This documentation covers the standard `Google Analytics`_ functionality available by
default in the CampaignChain Community Edition.

Features
--------

- Connect a Google Analytics account to CampaignChain with username and password
- Pull data from Google Analytics to relate the Website traffic during a
  campaign statistics of other Channels (e.g. likes of all Facebook posts).

Packages
--------

The standard Google Analytics functionality is being provided by CampaignChain, Inc.
through these packages:

- `campaignchain/channel-google-analytics`_
- `campaignchain/location-google-analytics`_

Although these modules are based on `Symfony bundles`_, they do not work
independently of CampaignChain.

Installation
------------

The above modules are included in the Community Edition by default.

Configuration
-------------

.. _google-analytics-oauth-app-configuration:

Before you can use Google Analytics data within CampaignChain, an OAuth app must be
created in Google:

#. Go to https://console.developers.google.com/apis/credentials, click on
   *Create credentials* and select *OAuth client ID*.
#. On the next page, select *Web application*.
#. Under *Authorized JavaScript origins*, enter the domain of your CampaignChain
   installation, e.g. http://mycampaignchain.com.
#. Provide this URL as an *Authorized redirect URI*:
   http://mycampaignchain.com/security/authentication/client/oauth/login?hauth.done=Google.
   Make sure that you specify the correct scheme (`http` or `https`).
#. The Callback URL's parts must be identical with the
   `router.request_context.host` and `router.request_context.scheme` parameters
   defined in the `app/config/parameters.yml` configuration file.
#. Once you have created the app, :ref:`connect to a Location <create-new-oauth-apps>`
   choosing Google Analytics as the Channel.
#. When the *Provide Application Credentials* screen comes up, go back to
   https://console.developers.google.com/apis/credentials, select your app and
   copy and paste the *Client ID* and the *Client Secret* and insert it in the
   *Provide Application Credentials* form.

Issues
------

Please post reports, questions, suggestions, etc. at
https://github.com/CampaignChain/campaignchain/issues.

.. _Google Analytics: https://google-analytics.com/
.. _campaignchain/channel-google-analytics: https://github.com/CampaignChain/channel-google-analytics
.. _campaignchain/location-google-analytics: https://github.com/CampaignChain/location-google-analytics
.. _Symfony bundles: http://symfony.com/doc/current/bundles.html
CampaignChain MailChimp
=======================

This documentation covers the standard `MailChimp`_ functionality available by
default in the CampaignChain Community Edition.

Features
--------

- Connect a MailChimp account to CampaignChain with username and password
- Assign a MailChimp email campaign into a CampaignChain campaign
- Schedule a MailChimp newsletter to be distributed by MailChimp at a given
  date and time
- Assign a responsible person to a MailChimp newsletter within CampaignChain
- Track the customer journey from an included link to the Location of a
  connected Channel (e.g. a Website page)
- Once a newsletter was posted, regularly collect statistical data about opens,
  clicks, etc.

Packages
--------

The standard MailChimp functionality is being provided by CampaignChain, Inc.
through these packages:

- `campaignchain/channel-mailchimp`_
- `campaignchain/location-mailchimp`_
- `campaignchain/activity-mailchimp`_
- `campaignchain/operation-mailchimp`_

Although these modules are based on `Symfony bundles`_, they do not work
independently of CampaignChain.

Installation
------------

The above modules are included in the Community Edition by default.

Configuration
-------------

.. _mailchimp-oauth-app-configuration:

Before you can manage a MailChimp email campaign from within CampaignChain, an
OAuth app must be created in MailChimp:

#. Go to https://admin.mailchimp.com/account/oauth2/ and register an app.
#. Fill out any required fields such as the application name and description.
#. Provide the host name of your CampaignChain instance as the *Redirect URL*
   (e.g. http://mydomain.com). Make sure that you specify the correct scheme
   (`http` or `https`).
#. The Callback URL's parts must be identical with the
   `router.request_context.host` and `router.request_context.scheme` parameters
   defined in the `app/config/parameters.yml` configuration file.
#. Once you have registered the app, :ref:`connect to a Location <connect-to-a-location>`
   choosing MailChimp as the Channel.
#. When the *Provide Application Credentials* screen comes up, go back to
   https://admin.mailchimp.com/account/oauth2/, select your app and copy and
   paste the *Client ID* and the *Client Secret* and insert it in the
   *Provide Application Credentials* form.

Issues
------

Please post reports, questions, suggestions, etc. at
https://github.com/CampaignChain/campaignchain/issues.

.. _MailChimp: http://mailchimp.com
.. _campaignchain/channel-mailchimp: https://github.com/CampaignChain/channel-mailchimp
.. _campaignchain/location-mailchimp: https://github.com/CampaignChain/location-mailchimp
.. _campaignchain/activity-mailchimp: https://github.com/CampaignChain/activity-mailchimp
.. _campaignchain/operation-mailchimp: https://github.com/CampaignChain/operation-mailchimp
.. _Symfony bundles: http://symfony.com/doc/current/bundles.html
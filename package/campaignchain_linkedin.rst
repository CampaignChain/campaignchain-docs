CampaignChain Linkedin
======================

This documentation covers the standard `Linkedin`_ functionality available by
default in the CampaignChain Community Edition.

Features
--------

- Connect a Linkedin user or company page to CampaignChain with username and
  password
- Assign a Linkedin message to a campaign
- Include 1 picture in a Linkedin status update
- Schedule a Linkedin message to automatically post it on Linkedin at a given
  date and time
- Assign a responsible person to a Linkedin update

.. note::

    To let CampaignChain regularly collect statistical data about likes and
    comments of Linkedin messages, you would have to apply to become a
    `Linkedin partner`_. Otherwise, CampaignChain won't have access to the
    respective REST API endpoints.

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

#. Go to https://www.linkedin.com/secure/developer (or https://www.linkedin.com/secure/developer?newapp=)
   and create a new application.
#. Fill out any required fields such as the application name and description.
#. Once you created the App, go to the *Authentication* menu entry.
#. Under *Default Application Permissions*, enable all permissions, i.e.
   `r_basicprofile`, `r_emailaddress`, `rw_company_admin`, `w_share`.
#. Under *OAuth 2.0*, provide the host name of your CampaignChain instance as
   the *Authorized Redirect URL* (e.g. http://mydomain.com). Make sure that you
   specify the correct scheme (`http` or `https`).
#. The Authorized Redirect URL's parts must be identical with the
   `router.request_context.host` and `router.request_context.scheme` parameters
   defined in the `app/config/parameters.yml` configuration file.
#. Once you saved all changes on the *Authentication* page, click on the
   *JavaScript* menu entry. There, add the host name of your CampaignChain
   installation as a *Valid SDK Domain*.
#. After you saved the changes to the *JavaScript* page,
   :ref:`connect to a Location <create-new-oauth-apps>` choosing Linkedin as the
   Channel.
#. When the *Provide Application Credentials* screen comes up, go back to
   the *Authentication* page of your Linkedin App to copy and paste the *Client
   ID* and the *Client Secret* and insert it in the *Provide Application
   Credentials* form.

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
.. _Linkedin partner: https://developer.linkedin.com/partner-programs
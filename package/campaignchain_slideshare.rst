CampaignChain SlideShare
========================

This documentation covers the standard `SlideShare`_ functionality available by
default in the CampaignChain Community Edition.

Features
--------

- Connect a SlideShare account to CampaignChain with username and password
- Assign a SlideShare slide deck to a campaign
- Schedule to make an already uploaded and private slide deck publicly available
  on SlideShare at a given date and time
- Within CampaignChain, assign a responsible person to a slide deck
- Once a slide deck was made public, regularly collect statistical data about
  Views, Favorites, Downloads, Comments

Packages
--------

The standard SlideShare functionality is being provided by CampaignChain, Inc.
through these packages:

- `campaignchain/channel-slideshare`_
- `campaignchain/location-slideshare`_
- `campaignchain/activity-slideshare`_
- `campaignchain/operation-slideshare`_

Although these modules are based on `Symfony bundles`_, they do not work
independently of CampaignChain.

Installation
------------

The above modules are included in the Community Edition by default.

Configuration
-------------

.. _slideshare-oauth-app-configuration:

Before you can post on SlideShare from within CampaignChain, an OAuth app must be
created in SlideShare:

#. Apply for an API key at http://www.slideshare.net/developers/applyforapi.
#. Fill out any required fields such as the application name and description.
#. Once you received the API key via email, :ref:`connect to a Location <connect-to-a-location>`
   choosing SlideShare as the Channel.
#. When the *Provide Application Credentials* screen comes up, insert the API
   key in the *Provide Application Credentials* form.

.. warning::

    If a SlideShare user was newly created with a Linkedin account, then please
    follow this workaround to make sure CampaignChain can access the SlideShare
    REST API: Explicitly set the SlideShare password by changing it from the
    Linkedin password to a new one at https://www.slideshare.net/ordnas/edit_manage_accounts.
    Only then, the new password for SlideShare will allow CampaignChain to
    access the SlideShare REST API.

    Also, when connecting the SlideShare account to CampaignChain, please be
    aware of the following: The SlideShare username is not the same as the
    Linkedin username. For Linkedin, the username might be identical with the
    account's email, while the SlideShare username can be found in the
    SlideShare profile URL. For example, *amariki* in http://www.slideshare.net/amariki.

Issues
------

Please post reports, questions, suggestions, etc. at
https://github.com/CampaignChain/campaignchain/issues.

.. _SlideShare: http://www.slideshare.net
.. _campaignchain/channel-slideshare: https://github.com/CampaignChain/channel-slideshare
.. _campaignchain/location-slideshare: https://github.com/CampaignChain/location-slideshare
.. _campaignchain/activity-slideshare: https://github.com/CampaignChain/activity-slideshare
.. _campaignchain/operation-slideshare: https://github.com/CampaignChain/operation-slideshare
.. _Symfony bundles: http://symfony.com/doc/current/bundles.html
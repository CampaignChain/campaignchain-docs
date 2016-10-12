Platform.sh
===========

This is a step-by-step guide on how to deploy CampaignChain Enterprise Edition
on Platform.sh.

CampaignChain Enterprise Edition can be installed out-of-the-box on Platform.sh,
either for production or development.

What's great about Platform.sh is that you can hook it up with GitHub to
automatically re-build and update CampaignChain on a Platform.sh server as soon
as changes to the code have been pushed to GitHub.

Development or Production
-------------------------

You can configure Platform.sh so that CampaignChain will be built and deployed
either for development or production use.

When in production mode, CampaignChain will be installed when you first create
the Platform.sh environment and afterwards, update routines will be executed
automatically upon every push to the GitHub repository which keep the database
up-to-date.

When in development mode, CampaignChain will be installed from scratch every
time a GitHub push happens. Additionally, sample data will be imported to
CampaignChain automatically. This means that all data created manually in the
database will be lost.

Configuring Platform.sh and GitHub
----------------------------------

First, you create a new Platform.sh project by following these steps:

#.  `Select a Platform.sh plan`_. Select "Development" if you would like to
    use Platform.sh as a live development environment or another plan if you'd
    like to use it for a production site.
#.  Add an `environment variable`_ to the Platform.sh environment with the name
    `campaignchain.env` and either the value `"dev"` for developing with
    CampaignChain, or `"prod"` to run CampaignChain EE for production use. Don't
    forget to put the value in quotes. Activate the `JSON value` checkbox.
#.  To allow Platform.sh to access the private GitHub repositories which are
    included in the distribution, proceed as follows: Copy the
    `SSH deploy key`_, then log into GitHub as the Platform.sh machine
    user. You can find the username and password in the credentials file
    you received with CampaignChain EE. Then add the Platform.sh deploy
    key, which you just copied, as a `new deploy key of the machine user`_.

Deploying on Platform.sh
------------------------

To sync the CampaignChain EE GitHub repository with Platform.sh, `install the
Platform.sh Command Line Interface`_ on your computer.

Then execute the following command. Replace `[project-id]` with the ID of your
Platform.sh project:

.. code:: bash

    platform integration:add --type=github --project=[project-id]
    --token=109d050c4afe3eb5a4c00938948dcd44835d86eb
    --repository=CampaignChain/campaignchain-ee --build-pull-requests=true
    --fetch-branches=true

.. _Select a Platform.sh plan: https://accounts.platform.sh/platform/buy-now
.. _environment variable: https://docs.platform.sh/administration/web/configure-environment.html#variables
.. _SSH deploy key: https://docs.platform.sh/development/private-repository.html#pull-code-from-a-private-git-repository
.. _new deploy key of the machine user: https://github.com/settings/keys
.. _install the Platform.sh Command Line Interface: https://docs.platform.sh/overview/cli.html#how-do-i-get-it
Development Mode
================

It is highly recommended that you configure CampaignChain to run in development
mode while you work on the code.

To enable development mode, set the ``campaignchain_dev``parameter to ``true``
in *app/config/parameters.yml*.

You should only do this prior to a fresh installation of CampaignChain and not
switch back to production mode for that installation.

When in development mode, the following happens:

require-dev in composer.json
----------------------------

While in development mode, CampaignChain will upon installation also register
CampaignChain modules which have been defined in the ``require-dev`` section of
your project's *composer.json* file.

Development Tools
-----------------

The navigation bar will display an icon to access various developer tools from
within the CampaignChain user interface.

.. image:: /images/developer/book/dev_tools.png
    :width: 600px

Modules Repositories
--------------------

You can specify modules repositories that should be used in development mode
instead of the ones you defined for the production instance.

The development modules repositories can be defined in the *campaignchain.yml*
of a distribution module.

.. code-block:: yaml

    modules:
        repositories:
            - http://www.example.com/modules/
        repositories-dev:
            - http://www.example.com/modules/dev/

In case no development modules repositories have been defined under
``repositories-dev``, CampaignChain will fall back and use the ones specified
under ``repositories``.
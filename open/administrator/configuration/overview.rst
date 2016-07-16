Overview
========

CampaignChain knows two types of configuration options:

* App-wide parameters
* Bundle-specific parameters

App-wide Parameters
-------------------

Parameters that configure the app-wide framework are prefixed with
``campaignchain.`` and defined in two files:

* *app/config/parameters.yml* contains the parameters that should be
  considered during installation under the ``parameters`` key.
* In *app/config/config_campaignchain.yml*, you will find other app-wide
  parameters (again under the ``parameters`` key), which contain default values
  that should be fine for most installations of CampaignChain.

For example, in *parameters.yml*, there's this option to define the route of
the tracking script:

.. code-block:: yaml

    parameters:
        campaignchain.env: prod
        campaignchain.tracking.js_route: /tracking.js

Bundle-specific Parameters
--------------------------

Each bundle or module might define its own configuration options. These are all
listed in *app/config/config_campaignchain_bundles.yml* under an alias for each
bundle, e.g. ``campaignchain_core``.

For example:

.. code-block:: yaml

    campaignchain_core:
        env: prod
        tracking:
            id_name: cctid
            js_mode: prod
            js_class: CCTracking
            js_init: cc
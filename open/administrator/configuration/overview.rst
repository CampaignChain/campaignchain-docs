Overview
========

CampaignChain knows two types of configuration options:

* App-wide parameters
* Bundle-specific parameters

App-wide Parameters
-------------------

Parameters that configure the app-wide framework are prefixed with
``campaignchain.`` and defined in two files:

* ``app/config/parameters.yml`` contains the parameters that should be
  considered during installation.
* In ``app/config/config_campaignchain.yml``, you will find other app-wide
  parameters, which contain default values that should be fine for most
  installations of CampaignChain.

Bundle-specific Parameters
--------------------------

Each bundle or module might define its own configuration options. These are all
listed in *app/config/config_campaignchain_bundles.yml* under an alias for each
bundle, e.g. ``campaignchain_core``.

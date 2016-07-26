Update Package
==============

The update feature is a package that is included in CampaignChain by default and
can also be used independently from CampaignChain as a regular Symfony bundle.

The update package offers you the ability to include update routines in multiple
separate CampaignChain modules or Symfony bundles. Essentially, it extends the
`DoctrineMigrationsBundle`_.

Installation
------------

CampaignChain
~~~~~~~~~~~~~

The ``campaignchain/update` Composer package is included in any CampaignChain
distribution by default. It will be installed automatically.

Symfony
~~~~~~~

First, install the package with

.. code-block:: bash

    $ composer require campaignchain/update "dev-master"

If everything worked, the update package can now be found at
``vendor/campaignchain/update``.

Finally, be sure to enable the bundle in ``AppKernel.php`` by including the
following:

.. code-block:: php

    // app/AppKernel.php
    public function registerBundles()
    {
        $bundles = array(
            //...
            new CampaignChain\UpdateBundle\CampaignChainUpdateBundle(),
        );
    }

Configuration
-------------

You can configure the default package name and the target directories for the
schema and update files in your ``config.yml``. The examples below are the
default values:

.. code-block:: yaml

    campaignchain_update:
        diff_package: campaignchain/core
        bundle:
            schema_dir: /Resources/update/schema
            data_dir: /Resources/update/data

Usage
-----

Learn how to use the update package in the tutorial on
:doc:`creating update routines </ce/developer/cookbook/module_update>`.

Issues
------

Please post reports, questions, suggestions, etc. at
https://github.com/CampaignChain/update/issues.

.. _DoctrineMigrationsBundle: https://symfony.com/doc/current/bundles/DoctrineMigrationsBundle/index.html
.. _CampaignChain/update: https://github.com/CampaignChain/update
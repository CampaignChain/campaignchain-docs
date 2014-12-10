Development
===========

If you would like to develop modules with CampaignChain, this page will explain 
how to install and configure all the relevant parts to get started.

0. Prerequisites
----------------

Verify that your system meets the :doc:`minimum system requirements <../requirements>`
to run CampaignChain.

1. Install Composer
-------------------

CampaignChain utilizes Composer for dependency management of PHP packages.

`Install Composer`_ to be able to install and update CampaignChain and related
packages.

2. Install Bower
----------------

For JavaScript components, CampaignChain makes use of Bower, which - you guessed
it - is a package manager for JavaScript code.

Before you can install Bower, you must first `install npm`_ which ships with
node.js.

Now install Bower through npm:

.. code-block:: bash

    $ npm install -g bower

3. Install Git
--------------

The CampaignChain source code is available on GitHub. Hence, please `install Git`_
to access the project and to commit to it.

4. Set up Database
------------------

CampaignChain has been tested to work with MySQL at the current point in time.
Hence, please set up a MySQL server and create a new database for CampaignChain.

5. Clone from GitHub
--------------------

Clone the CampaignChain CE source code from https://github.com/CampaignChain/campaignchain-ce

For example, if you set up GitHub with SSH, issue this command:

.. code-block:: bash

    $ git clone git@github.com:CampaignChain/campaignchain-ce.git

6. Require Additional Modules and Packages
------------------------------------------

If you would like to develop with additional Composer packages or have some
CampaignChain modules available right after installation, you can add them
now to the *composer.json* file in the root of the repository you just cloned.

For example, you could add these CampaignChain modules:

.. code-block:: yaml

    "require": {
        ...
        "campaignchain/operation-twitter": "dev-master",
        "campaignchain/operation-facebook": "dev-master",
        "campaignchain/operation-linkedin": "dev-master",
        "campaignchain/location-website": "dev-master"
    },

6. Install Base System
----------------------

In the root of CampaignChain, execute composer to install all the packages
required by the base system.

.. note::

    You must not execute below command as the root user on Linux.

.. code-block:: bash

    $ composer install --prefer-source

It will download and install all required packages and modules for the
CampaignChain base system. Please note that this might take a while.

7. Configure Base System
------------------------

During the process, Composer will ask in the command line to provide some
configuration parameters. Please make sure you check/provide at least the
following (default values in brackets):

.. code-block:: bash

    database_driver (pdo_mysql):
    database_host (127.0.0.1):
    database_port (null):
    database_name (campaignchain_ce):
    database_user (root):
    database_password (null):
    java_path (/usr/bin/java):

8. Configure Scheduler
----------------------

.. include:: ../include/_configure_scheduler.rst.inc

9. Start Server
---------------

Use PHP's built-in Web server to run CampaignChain.

.. code-block:: bash

    $ php app/console server:run

10. Installation Wizard
-----------------------

Hop over to http://localhost:8000/campaignchain/install.php and follow the instructions.

11. Install Modules
-------------------

You can easily add modules (e.g. to post on Twitter or Facebook) at http://localhost:8000/modules/new/.

Start Developing!
-----------------

You can now :doc:`start developing with CampaignChain </developer/book/index>` and create your
own bundles that include CampaignChain modules in the *src/* directory inside
the Symfony root.

If you would like to enhance or fix existing CampaignChain modules, they are
located at /path/to/campaignchain/vendor/campaignchain/.

.. _Install Composer: https://getcomposer.org/download/
.. _install Git: https://help.github.com/articles/set-up-git/
.. _install npm: http://nodejs.org/download/
.. _install Symfony through Composer: http://symfony.com/doc/current/book/installation.html
.. _BraincraftedBootstrapBundle: https://github.com/braincrafted/bootstrap-bundle
.. _SpBowerBundle: https://github.com/Spea/SpBowerBundle
.. _search for them on Packagist: https://packagist.org/search/?q=campaignchain
.. _Download YUI Compressor: https://github.com/yui/yuicompressor/releases
.. _Get CSSEmbed: https://github.com/nzakas/cssembed/downloads
.. _increase the PHP memory limit: https://getcomposer.org/doc/articles/troubleshooting.md#memory-limit-errors
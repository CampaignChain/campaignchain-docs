Community Edition (CE)
======================

The Community Edition has all relevant modules and sample data included so that you
can quickly try CampaignChain.

0. Preparation
---------------

1. Verify that your system meets the :doc:`minimum system requirements <../requirements>`
   to run CampaignChain.
2. Ensure that your MySQL server is running.

1. Download CampaignChain
-------------------------

Download the Community Edition from `www.campaignchain.com/download`_.

Extract the contents of the archive to a directory on your system.

Make sure that PHP has access to all files in the CampaignChain directory. On
Linux, you could issue this command:

.. code-block:: bash

    $ chown -R www-data:www-data /path/to/campaignchain

... with ``www-data`` being the HTTP server's user and group, respectively.

2. Set up Database
------------------

Launch your MySQL client of choice and create a new MySQL database for the
application.

3. Install Composer
-------------------

CampaignChain utilizes `Composer`_ for its package and modules management. Install
it with this command:

.. code-block:: bash

    $ curl -sS https://getcomposer.org/installer | php

4. Install Base System
----------------------

In the root of CampaignChain, execute this command (not as root user!):

.. code-block:: bash

    $ composer install

It will download and install all required packages and modules for the
CampaignChain base system. Please note that this might take a while.

At the end of the process, you will be asked in the command line to provide some
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


5. Configure CampaignChain Scheduler
------------------------------------

.. include:: ../include/_configure_scheduler.rst.inc

6. Start Server
---------------

Use PHP's built-in Web server to run CampaignChain.

.. code-block:: bash

    $ php app/console server:run

7. Installation Wizard
----------------------

Hop over to http://localhost:8000/campaignchain/install.php and follow the instructions.

8. Install Modules
------------------

You can easily add modules (e.g. to post on Twitter or Facebook) at http://localhost:8000/modules/new/.

Success!
--------

CampaignChain is now installed, configured and ready for use!

To make full use of CampaignChain's capabilities, you could now

1. :doc:`Configure Call to Action (CTA) tracking <../configuration/cta>`
2. :doc:`Learn how to create your first campaign and activity </user/get_started>`

.. _www.campaignchain.com/download: http://www.campaignchain.com/download
.. _Composer: https://getcomposer.org/download/
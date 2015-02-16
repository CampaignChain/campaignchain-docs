Community Edition (CE)
======================

The CampaignChain Community Edition has all basic modules included and you can 
easily add more of them inside the application.

0. Preparation
--------------

1. Verify that your system meets the :doc:`minimum system requirements <../requirements>`
   to run CampaignChain.
2. Ensure that your MySQL server is running.

1. Set up Database
------------------

Launch your MySQL client of choice and create a new MySQL database for the
application.

2. Install Composer
-------------------

CampaignChain utilizes `Composer`_ for its package and modules management. Install
it with this command:

.. code-block:: bash

    $ curl -sS https://getcomposer.org/installer | php

3. Install Bower
----------------

For JavaScript components, CampaignChain makes use of Bower, which - you guessed
it - is a package manager for JavaScript code.

Before you can install Bower, you must first `install npm`_ which ships with
node.js.

Now install Bower through npm:

.. code-block:: bash

    $ npm install -g bower

4. Install Base System
----------------------

In a folder of your choice, execute Composer to download all files of the
CampaignChain base system. Please note that this might take a while.

.. code-block:: bash

    $ composer create-project campaignchain/campaignchain-ce campaignchain 1.0.0-beta.1

5. Configure Base System
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

6. Clear Cache and Dump Assets
------------------------------

Once Composer is done, execute the following commands, still inside the
CampaignChain root folder:

.. code-block:: bash

    $ php app/console cache:clear --env=prod --no-debug

.. code-block:: bash

    $ php app/console assetic:dump --env=prod --no-debug

7. Configure CampaignChain Scheduler
------------------------------------

.. include:: ../include/_configure_scheduler.rst.inc

8. Start Server
---------------

Use PHP's built-in Web server to run CampaignChain.

.. code-block:: bash

    $ php app/console server:run

By default, the built-in Web server listens for connections on 127.0.0.1. If
you're planning to connect to the server over a network, you can specify the
network IP address that the server should use. For example, the command below
runs the Web server on port 80 of IP address 192.168.1.1:

.. code-block:: bash

    $ php app/console server:run 192.168.1.1:80
    
9. Installation Wizard
-----------------------

Hop over to http://localhost:8000/campaignchain/install.php and follow the instructions.

Success!
--------

CampaignChain is now installed, configured and ready for use!

To make full use of CampaignChain's capabilities, you could now

1. :doc:`Configure Call to Action (CTA) tracking <../configuration/cta>`
2. :doc:`Learn how to create your first campaign and activity </user/get_started>`

.. _install npm: http://nodejs.org/download/
.. _www.campaignchain.com/download: http://www.campaignchain.com/download
.. _Composer: https://getcomposer.org/download/
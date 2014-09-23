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
--------------------------

Download the Community Edition from `www.campaignchain.com/download`_.

Extract the contents of the archive to a directory on your system.

2. Set up Database
-------------------

Launch the MySQL command-line client and create a new MySQL database for the
application.

.. code-block:: mysql

    CREATE DATABASE campaignchain_db;

At the same time, create a user with full privileges to the new database, as
shown below:

.. code-block:: mysql

    GRANT ALL on campaignchain_db.* TO 'campaignchain'@'%' IDENTIFIED BY 'gue55me';

Edit the *app/config/parameters.yml* file and define the database host, name,
user and password.

*Example:*

.. code-block:: yaml

    parameters:
        database_driver: pdo_mysql
        database_host: 127.0.0.1
        database_port: null
        database_name: campaignchain_db
        database_user: campaignchain
        database_password: gue55me

From within the application's root directory, issue the following command which
will create the table structures in the database:

.. code-block:: bash

    $ php app/console doctrine:schema:update --force

3. Register Apps with Various Online Channels
-----------------------------------------------

To be able to post to Twitter, Facebook and LinkedIn from within CampaignChain,
register an App with these three services, by following the steps below:

1. Go to the following pages:

   - Twitter: https://apps.twitter.com
   - Facebook: https://developers.facebook.com/apps
   - LinkedIn: https://www.linkedin.com/secure/developer

2. Fill out any required fields.

Once you have registered a new app, you will receive a key and secret that will
be displayed to you under above pages.

Now, open the sample data file *vendor/campaignchain/distribution-ce/Resources/data/campaignchain/ce.yml*
and replace the text ``replaceme`` with the app key and secret provided by Twitter,
Facebook and LinkedIn.

.. code-block:: yaml

    # vendor/campaignchain/distribution-ce/Resources/data/campaignchain/ce.yml
    \CampaignChain\Security\Authentication\Client\OAuthBundle\Entity\Application:
        application1:
            resourceOwner: Twitter
            # Specify your Twitter Consumer Key and Secret here:
            key: replaceme
            secret: replaceme
        application2:
            resourceOwner: Facebook
            # Specify your Facebook App key and secret here:
            key: replaceme
            secret: replaceme
        application3:
            resourceOwner: LinkedIn
            # Specify your Facebook App key and secret here:
            key: replaceme
            secret: replaceme

Next, execute the below command to load the above sample data into CampaignChain:

.. code-block:: bash

    $ php app/console h4cc_alice_fixtures:load:files --manager=default --type=yaml --seed=42 vendor/campaignchain/distribution-ce/Resources/data/campaignchain/ce.yml

4. Configure CampaignChain Scheduler
-------------------------------------

.. include:: ../include/_configure_scheduler.rst.inc

5. Get Bitly Access Token
--------------------------

.. include:: ../include/_get_bitly_access_token.rst.inc

6. Start Server
---------------------

Use PHP's built-in Web server to run CampaignChain.

.. code-block:: bash

    $ php app/console server:run

7. Log In to CampaignChain
---------------------------

Point your Web browser to http://localhost:8000/ and log in with:

- **username**: admin
- **password**: test

8. Install Modules
--------------------

Visit the module installation screen at http://localhost:8000/system/modules/
and install all modules.

Success!
--------

CampaignChain is now installed, configured and ready for use!

To make full use of CampaignChain's capabilities, you could now

1. :doc:`Configure Call to Action (CTA) tracking <../configuration/cta>`
2. :doc:`Learn how to create your first campaign and activity </user/get_started>`

.. _www.campaignchain.com/download: http://www.campaignchain.com/download
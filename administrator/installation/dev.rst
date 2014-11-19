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

CampaignChain utilizes Composer for PHP package management.

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

3. Set up Database
------------------

CampaignChain has been tested to work with MySQL at the current point in time.
Hence, please set up a MySQL server and create a new database for CampaignChain.

4. Install and Configure Symfony
--------------------------------

CampaignChain is based on the Symfony PHP framework.

Hence, first `install Symfony through Composer`_.

4.1 Get YUI Compressor and CSSEmbed
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

`Download YUI Compressor`_ and install it into *app/Resources/java/yuicompressor.jar*.

`Get CSSEmbed`_ and save it in *app/Resources/java/cssembed.jar*.

4.2 Download Packages
~~~~~~~~~~~~~~~~~~~~~

Open the *composer.json* file in your Symfony root in an editor of your choice.

To be able to install development versions of CampaignChain packages, you should
specify the ``minimum-stability`` parameter in *composer.json* accordingly.

.. code-block:: json

    "minimum-stability": "dev",

Add the minimum required CampaignChain Composer packages to *composer.json*
in the Symfony root to have a fully functional CampaignChain installation.

.. code-block:: json

    "require": {
        "campaignchain/core": "dev-master",
        "campaignchain/campaign-scheduled": "dev-master",
        "campaignchain/milestone-scheduled": "dev-master",
        "campaignchain/report-analytics-metrics-per-activity": "dev-master"
    }

If you would like to add additional CampaignChain packages to your installation,
feel free to `search for them on Packagist`_.

For your convenience, here's a list of all currently available additional
CampaignChain packages, which will install other packages required by them:

.. code-block:: json

    "campaignchain/activity-facebook": "dev-master",
    "campaignchain/activity-linkedin": "dev-master",
    "campaignchain/activity-twitter": "dev-master",
    "campaignchain/doc-html": "dev-master"

Still in *composer.json*, add the post install and update scripts for the
`BraincraftedBootstrapBundle`_ and the `SpBowerBundle`_.

.. code-block:: json

    "scripts": {
        "post-install-cmd": [
            "Braincrafted\\Bundle\\BootstrapBundle\\Composer\\ScriptHandler::install",
            "Sp\\BowerBundle\\Composer\\ScriptHandler::bowerInstall"
        ],
        "post-update-cmd": [
            "Braincrafted\\Bundle\\BootstrapBundle\\Composer\\ScriptHandler::install",
            "Sp\\BowerBundle\\Composer\\ScriptHandler::bowerInstall"
        ]
    },

Then also add the Hybridauth library to the ``autoloader`` parameter in
*composer.json*, so that CampaignChain can use it.

.. code-block:: json

    "autoload": {
        "classmap": ["vendor/hybridauth/hybridauth/hybridauth"]
    }

4.3 Enable the Bundles
~~~~~~~~~~~~~~~~~~~~~~

Edit the *app/AppKernel.php* file and add the following lines inside the
``registerBundles()`` method to register the newly installed packages as Symfony
bundles.

::

    new Braincrafted\Bundle\BootstrapBundle\BraincraftedBootstrapBundle(),
    new Knp\Bundle\MenuBundle\KnpMenuBundle(),
    new Knp\Bundle\PaginatorBundle\KnpPaginatorBundle(),
    new SC\DatetimepickerBundle\SCDatetimepickerBundle(),
    new FOS\UserBundle\FOSUserBundle(),
    new CampaignChain\CoreBundle\CampaignChainCoreBundle(),
    new Bmatzner\FontAwesomeBundle\BmatznerFontAwesomeBundle(),
    new h4cc\AliceFixturesBundle\h4ccAliceFixturesBundle(),
    new FOS\JsRoutingBundle\FOSJsRoutingBundle(),
    new CampaignChain\Report\Analytics\MetricsPerActivityBundle\CampaignChainReportAnalyticsMetricsPerActivityBundle(),
    new CampaignChain\Hook\DueBundle\CampaignChainHookDueBundle(),
    new CampaignChain\Hook\AssigneeBundle\CampaignChainHookAssigneeBundle(),
    new CampaignChain\Campaign\ScheduledCampaignBundle\CampaignChainCampaignScheduledCampaignBundle(),
    new CampaignChain\Milestone\ScheduledMilestoneBundle\CampaignChainMilestoneScheduledMilestoneBundle(),
    new CampaignChain\Hook\DurationBundle\CampaignChainHookDurationBundle(),
    new Hpatoio\BitlyBundle\HpatoioBitlyBundle(),
    new Sp\BowerBundle\SpBowerBundle(),
    new Sonata\CoreBundle\SonataCoreBundle(),
    new Sonata\BlockBundle\SonataBlockBundle(),

If you have previously specified additional CampaignChain packages in
*composer.json*, then make sure you also register them here.

For your convenience, here's a list of other official bundles available for
CampaignChain that you could include in *app/AppKernel.php*:

::

    new CampaignChain\Channel\FacebookBundle\CampaignChainChannelFacebookBundle(),
    new CampaignChain\Security\Authentication\Client\OAuthBundle\CampaignChainSecurityAuthenticationClientOAuthBundle(),
    new CampaignChain\Activity\FacebookBundle\CampaignChainActivityFacebookBundle(),
    new CampaignChain\Channel\TwitterBundle\CampaignChainChannelTwitterBundle(),
    new CampaignChain\Activity\TwitterBundle\CampaignChainActivityTwitterBundle(),
    new CampaignChain\Operation\FacebookBundle\CampaignChainOperationFacebookBundle(),
    new CampaignChain\Operation\TwitterBundle\CampaignChainOperationTwitterBundle(),
    new CampaignChain\Location\TwitterBundle\CampaignChainLocationTwitterBundle(),
    new CampaignChain\Location\FacebookBundle\CampaignChainLocationFacebookBundle(),
    new CampaignChain\Channel\LinkedInBundle\CampaignChainChannelLinkedInBundle(),
    new CampaignChain\Location\LinkedInBundle\CampaignChainLocationLinkedInBundle(),
    new CampaignChain\Channel\WebsiteBundle\CampaignChainChannelWebsiteBundle(),
    new CampaignChain\Activity\LinkedInBundle\CampaignChainActivityLinkedInBundle(),
    new CampaignChain\Operation\LinkedInBundle\CampaignChainOperationLinkedInBundle(),
    new CampaignChain\Location\WebsiteBundle\CampaignChainLocationWebsiteBundle(),
    new CampaignChain\DistributionCeBundle\CampaignChainDistributionCeBundle(),

4.4 Add Configuration Options to *config.yml*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Configure the Symfony application as follows.

First, add the *assetic.yml* file which we are going to create later on top
of *config.yml* to the files it is supposed to import.

.. code-block:: yaml

    # app/config/config.yml
    imports:
        - { resource: assetic.yml }

Beneath the ``framework`` parameter, specify the ``translator`` configuration:

.. code-block:: yaml

    # app/config/config.yml
    framework:
        translator: ~

As part of the Twig configuration, specify a form template provided by
CampaignChain.

.. code-block:: yaml

    # app/config/config.yml
    twig:
        form:
            resources:
                - 'CampaignChainCoreBundle:Form:fields.html.twig'

Specify the core bundle of CampaignChain within the Assetic configuration.

.. code-block:: yaml

    # app/config/config.yml
    assetic:
        bundles:        ['CampaignChainCoreBundle']

Add the following configurations at the end of the *config.yml*. If you already
have some of the options configured, make sure you streamline it with the
configurations below.

.. code-block:: yaml

    # app/config/config.yml
    braincrafted_bootstrap:
        output_dir:
        assets_dir: %kernel.root_dir%/../vendor/twitter/bootstrap
        #assets_dir: %kernel.root_dir%/../vendor/twbs/bootstrap
        jquery_path: %kernel.root_dir%/../components/jquery/jquery.js
        less_filter: lessphp # "less", "lessphp" or "none"
        auto_configure:
            assetic: true
            twig: true
            knp_menu: true
            knp_paginator: true
        customize:
            variables_file: ~
            bootstrap_output: %kernel.root_dir%/../vendor/twitter/less/bootstrap.less
            bootstrap_template: BraincraftedBootstrapBundle:Bootstrap:bootstrap.less.twig

    sc_datetimepicker:
        picker: ~

    # FOS User Configuration
    fos_user:
        db_driver: orm # other valid values are 'mongodb', 'couchdb' and 'propel'
        firewall_name: main
        user_class: CampaignChain\CoreBundle\Entity\User
        group:
            group_class: CampaignChain\CoreBundle\Entity\Group

    hpatoio_bitly:
        # You Bitly access token. Visit [this page](https://bitly.com/a/oauth_apps) to get it.
        access_token: insert_here_you_bitly_access_token

        # These parameters are optionals !

        # Turn the profiler off
        profiler:

        # Turn file log on and specify log format
        file_log_format: default

    sp_bower:
        assetic:
            enabled: false
        bundles:
            CampaignChainCoreBundle: ~

    sonata_block:
        default_contexts: [sonata_page_bundle]
        blocks:
            sonata.block.service.text:
            sonata.block.service.rss:
            campaignchain.block.activity.upcoming.listgroup:
            campaignchain.block.milestone.upcoming.listgroup:
            campaignchain.block.campaign.ongoing.listgroup:
            campaignchain.block.rss:

4.5 Create *assetic.yml*
~~~~~~~~~~~~~~~~~~~~~~~~

Create a new file named *assetic.yml* in *app/config/* and include the following
content.

.. code-block:: yaml

    # app/config/assetic.yml
    assetic:
      java: /usr/bin/java
      filters:
        cssembed:
          jar: %kernel.root_dir%/Resources/java/cssembed.jar
        yui_js:
          jar: %kernel.root_dir%/Resources/java/yuicompressor.jar
        lessphp:
          file: %kernel.root_dir%/../vendor/oyejorge/less.php/lessc.inc.php
          apply_to: "\.less$"
      assets:
        campaignchain_base_css:
            inputs:
              - '@CampaignChainCoreBundle/Resources/public/css/campaignchain/base.css'
        campaignchain_base_js:
            inputs:
              - '@CampaignChainCoreBundle/Resources/public/js/campaignchain/base.js'
              - '@CampaignChainCoreBundle/Resources/public/components/ScrollToFixed/jquery-scrolltofixed.js'
        jquery_js:
            inputs:
                - %kernel.root_dir%/../vendor/components/jquery/jquery.js
            filters: [?yui_js]
        moment_js:
            inputs:
                - '@CampaignChainCoreBundle/Resources/public/components/moment/moment.js'
                - '@CampaignChainCoreBundle/Resources/public/components/moment-timezone/builds/moment-timezone-with-data.js'
        bootstrap_js:
            inputs:
                - '%kernel.root_dir%/../vendor/twitter/bootstrap/js/transition.js'
                - '%kernel.root_dir%/../vendor/twitter/bootstrap/js/alert.js'
                - '%kernel.root_dir%/../vendor/twitter/bootstrap/js/modal.js'
                - '%kernel.root_dir%/../vendor/twitter/bootstrap/js/dropdown.js'
                - '%kernel.root_dir%/../vendor/twitter/bootstrap/js/scrollspy.js'
                - '%kernel.root_dir%/../vendor/twitter/bootstrap/js/tab.js'
                - '%kernel.root_dir%/../vendor/twitter/bootstrap/js/tooltip.js'
                - '%kernel.root_dir%/../vendor/twitter/bootstrap/js/popover.js'
                - '%kernel.root_dir%/../vendor/twitter/bootstrap/js/button.js'
                - '%kernel.root_dir%/../vendor/twitter/bootstrap/js/collapse.js'
                - '%kernel.root_dir%/../vendor/twitter/bootstrap/js/carousel.js'
                - '%kernel.root_dir%/../vendor/twitter/bootstrap/js/affix.js'
            filters: [?yui_js]
        bootstrap_less:
            inputs:
                - '%kernel.root_dir%/../vendor/twitter/bootstrap/less/bootstrap.less'
            filters: [lessphp,cssembed]
        braincrafted_bootstrap:
            less_filter: lessphp
        select2_js:
            inputs:
                - '%kernel.root_dir%/..//vendor/ivaynberg/select2/select2.js'
        select2_css:
            inputs:
                - '%kernel.root_dir%/../vendor/ivaynberg/select2/select2.css'
                - '%kernel.root_dir%/../vendor/ivaynberg/select2/select2-bootstrap.css'
        datatables_js:
            inputs:
                - '%kernel.root_dir%/../vendor/datatables/datatables/media/js/jquery.dataTables.js'
                - '%kernel.root_dir%/../vendor/datatables/datatables/examples/resources/bootstrap/3/dataTables.bootstrap.js'
        datatables_css:
            inputs:
                - '%kernel.root_dir%/../vendor/datatables/datatables/examples/resources/bootstrap/3/dataTables.bootstrap.css'
        daterangepicker_js:
            inputs:
              - '@CampaignChainCoreBundle/Resources/public/components/bootstrap-daterangepicker/daterangepicker.js'
        daterangepicker_css:
            inputs:
              - '@CampaignChainCoreBundle/Resources/public/components/bootstrap-daterangepicker/daterangepicker-bs3.css'
        # DHTMLXGantt
        dhtmlxgantt_js:
            inputs:
                - '@CampaignChainCoreBundle/Resources/public/components/gantt/codebase/dhtmlxgantt.js'
        dhtmlxgantt_tooltip_js:
            inputs:
                - '@CampaignChainCoreBundle/Resources/public/components/gantt/codebase/ext/dhtmlxgantt_tooltip.js'
        campaignchain_dhtmlxgantt_toolbar_js:
            inputs:
                - '@CampaignChainCoreBundle/Resources/public/js/campaignchain/dhtmlxgantt/toolbar.js'
        campaignchain_dhtmlxgantt_pre_init_js:
            inputs:
                - '@CampaignChainCoreBundle/Resources/public/js/campaignchain/dhtmlxgantt/pre_init.js'
        campaignchain_dhtmlxgantt_post_init_js:
            inputs:
                - '@CampaignChainCoreBundle/Resources/public/js/campaignchain/dhtmlxgantt/post_init.js'
        dhtmlxgantt_css:
            inputs:
                - '@CampaignChainCoreBundle/Resources/public/components/gantt/codebase/dhtmlxgantt.css'
                - '@CampaignChainCoreBundle/Resources/public/css/campaignchain/dhtmlxgantt.css'
        flot_js:
            inputs:
                - '@CampaignChainCoreBundle/Resources/public/components/flot/jquery.flot.js'
                - '@CampaignChainCoreBundle/Resources/public/components/flot/jquery.flot.time.js'
                - '@CampaignChainCoreBundle/Resources/public/components/flot/jquery.flot.symbol.js'
        flot_comments_js:
            inputs:
                - '@CampaignChainCoreBundle/Resources/public/components/jquery.flot.comments/jquery.flot.comments.js'
        flot_tooltip_js:
            inputs:
                - '@CampaignChainCoreBundle/Resources/public/components/flot.tooltip/js/jquery.flot.tooltip.js'
        campaignchain_flot_css:
            inputs:
                - '@CampaignChainCoreBundle/Resources/public/css/campaignchain/flot.css'
        fullcalendar_js:
            inputs:
                - '@CampaignChainCoreBundle/Resources/public/components/fullcalendar/dist/fullcalendar.js'
        fullcalendar_css:
            inputs:
                - '@CampaignChainCoreBundle/Resources/public/components/fullcalendar/dist/fullcalendar.css'
                - '@CampaignChainCoreBundle/Resources/public/css/campaignchain/fullcalendar.css'
        countdown_js:
            inputs:
                - '@CampaignChainCoreBundle/Resources/public/components/jquery.countdown/dist/jquery.countdown.js'
      bundles:
        - CampaignChainCoreBundle
        - CampaignChainReportAnalyticsMetricsPerActivityBundle
        - FOSUserBundle
        - CampaignChainMilestoneScheduledMilestoneBundle

4.6 Specify *security.yml*
~~~~~~~~~~~~~~~~~~~~~~~~~~

Replace everything that is already in the *app/config/security.yml* file with
the below configuration.

.. code-block:: yaml

    security:
        role_hierarchy:
            ROLE_ADMIN:       ROLE_USER
            ROLE_SUPER_ADMIN: ROLE_ADMIN

        providers:
            fos_userbundle:
                id: fos_user.user_provider.username

        encoders:
            FOS\UserBundle\Model\UserInterface: sha512

        # set access_strategy to unanimous, else you may have unexpected behaviors
        access_decision_manager:
            strategy: unanimous

        firewalls:
            # defaut login area for standard users
            main:
                pattern:     ^/
                form_login:
                    provider:      fos_userbundle
                    csrf_provider: form.csrf_provider
                    login_path: /login
                logout: true
                anonymous:   true

        access_control:
           # URL of FOSUserBundle which need to be available to anonymous users
            - { path: ^/_wdt, role: IS_AUTHENTICATED_ANONYMOUSLY }
            - { path: ^/_profiler, role: IS_AUTHENTICATED_ANONYMOUSLY }
            - { path: ^/login$, role: IS_AUTHENTICATED_ANONYMOUSLY }
            - { path: ^/admin/, role: ROLE_ADMIN }

            # AsseticBundle paths used when using the controller for assets
            - { path: ^/js/, role: IS_AUTHENTICATED_ANONYMOUSLY }
            - { path: ^/css/, role: IS_AUTHENTICATED_ANONYMOUSLY }

            # URL of FOSUserBundle which need to be available to anonymous users
            - { path: ^/register, role: IS_AUTHENTICATED_ANONYMOUSLY }
            - { path: ^/resetting, role: IS_AUTHENTICATED_ANONYMOUSLY }

            # Secured part of the site
            - { path: ^/, role: ROLE_USER }
            - { path: ^/, roles: IS_AUTHENTICATED_ANONYMOUSLY }

4.7 Add the Routes
~~~~~~~~~~~~~~~~~~

In the *app/config/routing.yml* file, add the following routes for the minimum
required packages to develop with CampaignChain.

.. code-block:: yaml

    groganz_campaignchain_hook_duration:
        resource: "@CampaignChainHookDurationBundle/Resources/config/routing.yml"
        prefix:   /

    groganz_campaignchain_milestone_scheduled_milestone:
        resource: "@CampaignChainMilestoneScheduledMilestoneBundle/Resources/config/routing.yml"
        prefix:   /

    groganz_campaignchain_campaign_scheduled_campaign:
        resource: "@CampaignChainCampaignScheduledCampaignBundle/Resources/config/routing.yml"
        prefix:   /

    groganz_campaignchain_hook_assignee:
        resource: "@CampaignChainHookAssigneeBundle/Resources/config/routing.yml"
        prefix:   /

    groganz_campaignchain_hook_due:
        resource: "@CampaignChainHookDueBundle/Resources/config/routing.yml"
        prefix:   /

    groganz_campaignchain_report_analytics_metrics_per_activity:
        resource: "@CampaignChainReportAnalyticsMetricsPerActivityBundle/Resources/config/routing.yml"
        prefix:   /

    groganz_campaignchain_core:
        resource: "@CampaignChainCoreBundle/Resources/config/routing.yml"
        prefix:   /

If you previously added more CampaignChain packages to *composer.json*, make
sure you also add the corresponding routes.

Here are the routing entries for all other official CampaignChain bundles
currently available:

.. code-block:: yaml

    groganz_campaignchain_location_website:
        resource: "@CampaignChainLocationWebsiteBundle/Resources/config/routing.yml"
        prefix:   /

    groganz_campaignchain_operation_linked_in:
        resource: "@CampaignChainOperationLinkedInBundle/Resources/config/routing.yml"
        prefix:   /

    groganz_campaignchain_activity_linked_in:
        resource: "@CampaignChainActivityLinkedInBundle/Resources/config/routing.yml"
        prefix:   /

    groganz_campaignchain_channel_website:
        resource: "@CampaignChainChannelWebsiteBundle/Resources/config/routing.yml"
        prefix:   /

    groganz_campaignchain_location_linked_in:
        resource: "@CampaignChainLocationLinkedInBundle/Resources/config/routing.yml"
        prefix:   /

    groganz_campaignchain_channel_linked_in:
        resource: "@CampaignChainChannelLinkedInBundle/Resources/config/routing.yml"
        prefix:   /

    groganz_campaignchain_location_facebook:
        resource: "@CampaignChainLocationFacebookBundle/Resources/config/routing.yml"
        prefix:   /

    groganz_campaignchain_location_twitter_user:
        resource: "@CampaignChainLocationTwitterBundle/Resources/config/routing.yml"
        prefix:   /

    groganz_campaignchain_operation_twitter:
        resource: "@CampaignChainOperationTwitterBundle/Resources/config/routing.yml"
        prefix:   /

    groganz_campaignchain_operation_facebook:
        resource: "@CampaignChainOperationFacebookBundle/Resources/config/routing.yml"
        prefix:   /

    groganz_campaignchain_activity_twitter:
        resource: "@CampaignChainActivityTwitterBundle/Resources/config/routing.yml"
        prefix:   /

    groganz_campaignchain_channel_twitter:
        resource: "@CampaignChainChannelTwitterBundle/Resources/config/routing.yml"
        prefix:   /

    groganz_campaignchain_activity_facebook:
        resource: "@CampaignChainActivityFacebookBundle/Resources/config/routing.yml"
        prefix:   /

    groganz_campaignchain_security_authentication_client_o_auth:
        resource: "@CampaignChainSecurityAuthenticationClientOAuthBundle/Resources/config/routing.yml"
        prefix:   /

    groganz_campaignchain_channel_facebook:
        resource: "@CampaignChainChannelFacebookBundle/Resources/config/routing.yml"
        prefix:   /

4.8 Run Composer and Bower
~~~~~~~~~~~~~~~~~~~~~~~~~~

Run Composer from inside the Symfony root to install the CampaignChain packages.

.. code-block:: bash

    $ composer update

It might take a couple of minutes for Composer to download and install all
required packages.

.. note::

    Should Composer display the "Your requirements could not be resolved to an
    installable set of packages" error and the cause is that it cannot
    properly resolve the ``symfony/symfony`` dependency, then using the ~ operator
    in the version definition might help. For example, change ``"2.5.*"`` to ``"~2.5"`` for
    ``"symfony/symfony"`` in *composer.json*.

    In case you run into a ``Allowed memory size of XXXXXX bytes exhausted`` error,
    please `increase the PHP memory limit`_.

To run Bower and install the required JavaScript packages, execute this command
from within Symfony's root.

.. code-block:: bash

    $ php app/console sp:bower:install

5. Get Bitly Access Token
-------------------------

.. include:: ../include/_get_bitly_access_token.rst.inc

6. Dump and Install Assets
--------------------------

Make Symfony move assets such as JavaScript and CSS files as well as images to
the *web/* directory.

.. code-block:: bash

    $ php app/console assets:install web
    $ php app/console assetic:dump

7. Configure Scheduler
----------------------

.. include:: ../include/_configure_scheduler.rst.inc

8. Create Database Tables
-------------------------

In case you did not already specify database access credentials when installing
Symfony through Composer, please do so now in *app/config/parameters.yml*.

Run this command inside the Symfony root to create the CampaignChain database
tables.

.. code-block:: bash

    $ php app/console doctrine:schema:update --force

9. Start Server
---------------

Use PHP's built-in web server to run CampaignChain.

.. code-block:: bash

    $ php app/console server:run

10. Log in as Admin
-------------------

Create an admin account with this command inside the Symfony root. Replace
``you@example.com`` and ``yourpassword`` with the email and password you prefer.

.. code-block:: bash

    $ php app/console fos:user:create admin --super-admin you@example.com yourpassword

Point your Web browser to http://localhost:8000/ and log in with username
``admin`` and the password you provided in the above command.

11. Install Modules
-------------------

Visit the module installation screen at http://localhost:8000/system/modules/
and install all modules.

Start Developing!
-----------------

You can now :doc:`start developing with CampaignChain </developer/book/index>` and create your
own bundles that include CampaignChain modules in the *src/* directory inside
the Symfony root.

.. _Install Composer: https://getcomposer.org/download/
.. _install npm: http://nodejs.org/
.. _install Symfony through Composer: http://symfony.com/doc/current/book/installation.html
.. _BraincraftedBootstrapBundle: https://github.com/braincrafted/bootstrap-bundle
.. _SpBowerBundle: https://github.com/Spea/SpBowerBundle
.. _search for them on Packagist: https://packagist.org/search/?q=campaignchain
.. _Download YUI Compressor: https://github.com/yui/yuicompressor/releases
.. _Get CSSEmbed: https://github.com/nzakas/cssembed/downloads
.. _increase the PHP memory limit: https://getcomposer.org/doc/articles/troubleshooting.md#memory-limit-errors
Module Basics
=============

CampaignChain uses a modular architecture, allowing developers to integrate any
online channel along with its locations, activities and operations. 

This document provides an overview of common concepts that developers should 
know when developing CampaignChain modules, e.g. for custom channels, locations,
activities and operations.

Framework
---------
Symfony
~~~~~~~
CampaignChain has been built on top of the PHP-based `Symfony framework`_.
Therefore, custom modules should also be developed with Symfony.

Doctrine
~~~~~~~~
Within Symfony, CampaignChain uses Doctrine_ as
its Object-Relation Mapper (ORM). This allows usage of various databases 
in the back-end.

Bootstrap 3
~~~~~~~~~~~
CampaignChain's GUI is based on `Bootstrap 3`_ and module
developers should follow its best practices of responsive design.

Types of Modules
----------------

CampaignChain's core can be extended through various types of modules, each covering
a certain feature set. The following pre-defined types exist:

* *Activity*, e.g. post on Facebook or Twitter.
* *Campaign*, to develop custom campaign functionality (e.g. nurtured campaigns).
* *Channel*, to connect to channels such as Facebook or Twitter.
* *Location*, to manage e.g. various Facebook pages.
* *Milestone*, e.g. to develop a new kind of milestone besides the default 
  one with a due date.
* *Operation*, similar to Activity module type.
* *Report*, to create custom analytics, budget or sales reports for ROI monitoring.
* *Security*, e.g. functionality for channels to log in to third-party systems.
* *Distribution*, an aggregation of bundles and system-wide configuration, e.g.
  the `CampaignChain Community Edition`_.

The concepts in this document apply to all types of modules. 

* For information specific to building channel and location modules, refer to 
  the `Channels and Locations`_ page.

* For information specific to building activity and operation modules, refer to 
  the `Activities and Operations`_ page.

Packaging
---------
CampaignChain modules are developed as `Symfony bundles`_. One Symfony bundle must contain
at least one CampaignChain module and can contain various CampaignChain modules of the
same type.

To allow CampaignChain to install a bundle along with its module(s), the bundle
must contain the following two configuration files in its root:

* *composer.json*: CampaignChain modules (residing inside a Symfony bundle), are
  installed/distributed as Composer_ packages. This file holds information relevant to Composer.

* *campaignchain.yml*: This file holds all the CampaignChain-specific module
  configuration parameters.

Since CampaignChain is built on top of the Symfony framework, modules can use
functionality provided by other modules mainly through `Symfony services`_.

Versioning
----------

The version number of module packages for CampaignChain must follow the syntax
laid out in the `Semantic Versioning`_ specification.

Bundle Generation
-----------------
When building an CampaignChain module, the first step is to `create a new Symfony
bundle`_.

Configuration Files
-------------------
Every bundle with CampaignChain modules must have the following two configuration
files, which are essential for CampaignChain to correctly identify and integrate
the included module(s).

These files must be located in the root of the bundle directory.

composer.json
~~~~~~~~~~~~~
The bundle's *composer.json* file follows standard Composer conventions. 
The *type* parameter must belong to the set of pre-defined module types as 
outlined previously. Here is a list of parameters typically seen in this file:


* require: A list of package dependencies
* description: A human-readable description for the bundle
* keywords: Additional descriptive keywords for the bundle
* homepage: A link to the bundles's website
* license: The license under which the bundle and its modules are made available
* authors: A list of package authors

*Example:*

.. code-block:: json

 {
    "name": "campaignchain/channel-twitter",
    "description": "Connect with Twitter.",
    "keywords": ["twitter","oauth"],
    "type": "campaignchain-channel",
    "homepage": "http://www.groganz.com",
    "license": "Proprietary",
    "authors": [
        {
            "name": "Sandro Groganz",
            "email": "sandro@campaignchain.com"
        }
    ],
    "require": {
        "campaignchain/core": "dev-master",
        "campaignchain/security-authentication-client-oauth": "dev-master"
    }
 }

In addition to the `schema of the composer.json file`_ developers of CampaignChain
modules should also follow the best practices outlined below.

Parameter *name*
................
The name of the bundle. Typically this is the application name or vendor 
name, followed by a separating slash (/), then the module type followed 
by a dash and the bundle's purpose.

The schematic representation of the syntax is:
<application or vendor name>/<bundle type>-<purpose of bundle>

*Example: campaignchain/channel-twitter*

Parameter *type*
................
The type of the bundle, which must be one of

* campaignchain-channel
* campaignchain-location
* campaignchain-activity
* campaignchain-operation
* campaignchain-report
* campaignchain-campaign
* campaignchain-security
* campaignchain-milestone

Custom types are not supported and CampaignChain will display an error if it
encounters a type value outside the above allowed set.

Other Parameters Required by CampaignChain
..........................................

* description: A human-readable description for the bundle
* keywords: Additional descriptive keywords for the bundle
* homepage: A link to the bundles's website
* license: The license under which the bundle and its modules are made available
* authors: A list of package authors

campaignchain.yml
~~~~~~~~~~~~~~~~~
The bundle's *campaignchain.yml* file specifies all CampaignChain modules contained in
the bundle. Per module, it defines parameters such as the internal name of 
the module, used to reference it from other modules, as well as any associated 
`Symfony routes`_ and `Symfony services`_ or CampaignChain hooks. The information in
the file varies depending on the module type and requirements.

The typical structure of the *campaignchain.yml* file is as follows:

.. code-block:: text

  modules:
      |module-identifier|:
          display_name: |display name|
          channels:
              - |channel identifier|
              - |channel identifier|
              ...
          services:
              - job: |service identifier|
          routes:
              - new: |route identifier|
              - edit: |route identifier|
              - edit_modal: |route identifier|
              - edit_api: |route identifier|
          hooks:
              - |hook-name|: |true|false|
              - |hook-name|: |true|false|
              ...
          system:
              navigation:
                  settings:
                      - [|Nav item name|, |symfony_route|]
                      ...
                  ...
      |module-identifier|:
          ...

*Example: An activity module's campaignchain.yml file lists the channels the
activity belongs to and the Symfony routes to create and edit new activities.*

.. code-block:: yaml

 modules:
    campaignchain-twitter-update-status:
        display_name: 'Update Status'
        channels:
            - campaignchain/channel-twitter/campaignchain-twitter
        services:
            job: campaignchain.activity.twitter.job.update_status
        routes:
            new: campaignchain_activity_twitter_update_status_new
            edit: campaignchain_activity_twitter_update_status_edit
            edit_modal: campaignchain_activity_twitter_update_status_edit_modal
            edit_api: campaignchain_activity_twitter_update_status_edit_api
        hooks:
            campaignchain-due: true
            campaignchain-duration: false
            campaignchain-assignee: true

Module Identifier
.................
The module's identifier should be provided as the child of the *modules* 
parameter. Multiple modules can be specified in this way. The recommended 
syntax of the module identifier is to use dashes (-) to separate words, 
which helps to separate it from the parameters which use underscores. 
Furthermore, the identifier should start with an application or vendor 
name followed by a string that best captures the purpose of the module.

In sum, the recommended syntax is:
<application or vendor name>-<purpose of module>

*Example: campaignchain-twitter-update-status*

.. note::
  It is important to note that **the module identifier must be unique per 
  module type across bundles**. In other words: In a bundle, only CampaignChain
  modules of the same type are allowed and the identifier of each module 
  must be unique in all bundles containing the same type of modules.

Parameter *display_name*
........................
All modules have to specify the module name that will be displayed in 
CampaignChain's graphical user interface by providing a string as the value of
the *display_name* parameter.

Parameter *services*
....................
A module can define the following services to be consumed by CampaignChain.

* job: This service will be called by CampaignChain's scheduler to automatically
  execute functionality, e.g. publishing a scheduled post to Twitter.

Parameter *routes*
..................
Within the *campaignchain.yml* configuration file, CampaignChain recognizes four types
of Symfony routes.

* new: The route to invoke when creating a new (channel/location/activity/operation)
* edit: The route to invoke when editing an existing (channel/location/activity/operation)
* edit_modal: The route to invoke for the pop-up view of the 'edit' route
* edit_api: The route to invoke for the submit action of the 'edit_modal' route

Parameter *hooks*
.................
Hooks can be assigned to a module by specifying the hook's identifier and 
*true* to activate it or *false* to deactivate it. If a hook is omitted, 
CampaignChain will regard it as inactive.

Parameter *system*
..................
This parameter allows a module to define system-wide configuration options. For
example, to add a new navigation item to the settings navigation menu available
in the header of CampaignChain's graphical user interface.

Parameters Specific to a Module Type
....................................
Some module types require certain parameters in the *campaignchain.yml* configuration
file to be defined. For example, an Activity module should list at least one
related channel module. Similarly, an Operation module must define
whether it creates a Location or not. You will find more detailed information in the
documentation related to a specific module type.

.. _Symfony framework: http://symfony.com/
.. _Doctrine: http://doctrine-project.org
.. _Bootstrap 3: http://getbootstrap.com
.. _Channels and Locations: channels_locations.rst
.. _Activities and Operations: activities_operations.rst
.. _Symfony bundles: http://symfony.com/doc/current/cookbook/bundles/index.html
.. _Composer: https://getcomposer.org
.. _Symfony services: http://symfony.com/doc/current/book/service_container.html
.. _create a new Symfony bundle: http://symfony.com/doc/current/bundles/SensioGeneratorBundle/commands/generate_bundle.html
.. _schema of the composer.json file: https://getcomposer.org/doc/04-schema.md
.. _Symfony routes: http://symfony.com/doc/current/book/routing.html
.. _CampaignChain Community Edition: https://github.com/CampaignChain/distribution-ce
.. _Semantic Versioning: http://semver.org/
Creating Update Routines for Your Module
========================================

When you :doc:`update a CampaignChain installation </ce/administrator/deployment/update>`,
the automatic update functionality takes the update routines provided with each
CampaignChain module and applies them to the database schema and user-generated
data (e.g. data in the database or in the file system).

When developing your own modules, it is best practice to include such update
routines as soon as something changes in your module that affects the database
schema or user-generated data.

CampaignChain ships with commands that support developers in creating and
testing such update routines.

Prerequisites
-------------

Automatic updates only work if you `installed CampaignChain as explained in the
README.md file`_.

To verify whether this is the case, please check whether the following tables
exist in your CampaignChain database and that they are populated with data:

- *campaignchain_update_schema*
- *campaignchain_update_data*

.. warning::

    If you installed CampaignChain prior to July 23rd, 2016, then the
    automatic update functionality is not included. Please make a new
    installation from scratch. If you need help with migrating your data, please
    `contact us`_.

Schema Update
-------------

Whenever you add or modify an `entity class`_ in your CampaignChain module, it
affects the database. To keep track of changes and allow for automatic update of
a CampaignChain installation, there are commands that ship with CampaignChain:

- *campaignchain:schema:diff*: Automatically generates a PHP class that includes
  SQL commands that define how to modify the database schema as per your changes.
- *campaignchain:update:schema*: Apply the changes to the database schema.

Given that our schema update functionality is based on the
`Doctrine Migration Bundle`_, you could also use the following command:

- *doctrine:migrations:status*
- *doctrine:migrations:migrate*

.. warning::

    CampaignChain's update functionality extends that of the Doctrine Migration
    Bundle to manage update routines contained in multiple modules. Hence, you
    should not use other Doctrine Migration commands unless you understand
    the inner workings of the Doctrine Migration Bundle in relation to
    CampaignChain's module system.

.. note::

    As of now, schema updates are only available for MySQL.

Generate a Schema Diff
~~~~~~~~~~~~~~~~~~~~~

Whenever you add or modify an entity class in a module, you should run the
*diff* command for that specific module. This ensures that the generated *diff*
file includes only the changes for that single module.

.. note::

    It is best practice to provide update routines per CampaignChain module.

To create a *diff* file, execute the following command in the root of your
CampaignChain installation:

.. code-block:: bash

    $ php app/console campaignchain:schema:diff

You will be asked to provide the `Composer package name`_, so that the command
knows where to put the *diff* file. For example: *acme/my-package*. Once you
provided the name, the command will place a schema update file in the directory
*/Resources/udpate/schema* of your module. The name of the file is
*Version\*.php*.

Inside the schema update file, you will find the SQL commands for up- or
downgrading. For example:

.. code-block:: php

    $this->addSql('RENAME TABLE acme_my_bundle_activity_sensors TO acme_my_bundle_activity_iot_devices');

If you are working on the same module for a longer time, it becomes cumbersome
to always provide the package name. To make life easier, you can configure a
default package name in *app/config/parameters.yml* with:

.. code-block:: yaml

    campaignchain_update:
        diff_package: acme/my-package

Test the Schema Update
~~~~~~~~~~~~~~~~~~~~~~

To test your schema update routines, run this command in the root of your
CampaignChain installation:

.. code-block:: bash

    $ php app/console campaignchain:update:schema

You should now see the results of the applied changes:

.. code-block:: bash

    Migrating up to 20160723191847 from 20160717050911

      ++ migrating 20160723191847

         -> RENAME TABLE acme_my_bundle_activity_sensors TO acme_my_bundle_activity_iot_devices

      ++ migrated (0.05s)

      ------------------------

      ++ finished in 0.05s
      ++ 1 migrations executed
      ++ 1 sql queries

If you would like to manually change something in the SQL and then test the
schema update routine again, first downgrade your installation to the
previous version, so that it does not include your module's updates. Issue this
command to find the previous version:

.. code-block:: bash

    $ php app/console doctrine:migrations:status

In the displayed information, find the entry for the *Previous Version*:

.. code-block:: bash

    >> Previous Version:                                   2016-07-17 05:09:11 (20160717050911)

Roll back your CampaignChain installation by issuing this command and the
version number provided in above entry:

.. code-block:: bash

    $ php app/console doctrine:migrations:migrate 20160717050911

Once you confirmed to downgrade, you run CampaignChain's schema update
command again to apply the changes:

.. code-block:: bash

    $ php app/console campaignchain:update:schema

Data Update
-----------

If changes in your module affect user-generated data, then you should use the
data update functionality available with CampaignChain. Data updates are
similar to schema updates, but they require more manual work.

Create the Data Update Class
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Start by defining the data update PHP class, which is supposed to implement
the data update interface and to reside in the */Resources/update/data*
folder of your module.

.. code-block:: php

    <?php
    // /Resources/update/data/UpdateAddIdToName.php

    namespace Acme\MyBundle\Resources\update\data;

    use CampaignChain\UpdateBundle\Service\DataUpdateInterface;
    use Doctrine\ORM\EntityManager;
    use Symfony\Component\Console\Style\SymfonyStyle;

    class UpdateAddIdToName implements DataUpdateInterface
    {
        private $entityManager;

        public function __construct(EntityManager $entityManager)
        {
            $this->entityManager = $entityManager;
        }

        public function getVersion()
        {
            return 20160723191847;
        }

        public function getDescription()
        {
            return [
                'Adding the device ID to its name to make it globally unique',
            ];
        }

        public function execute(SymfonyStyle $io = null)
        {
            $iotDevices = $this->entityManager
                ->getRepository('AcmeMyBundle:IotDevice')
                ->findAll();

            if (empty($iotDevices)) {
                $io->text('There is no IoT device to process');

                return true;
            }

            foreach ($iotDevices as $iotDevice) {
                $iotDevice->setName($iotDevice->getId().'-'.$iotDevice->getName());
                $this->entityManager->persist($iotDevice);
            }

            $this->entityManager->flush();

            return true;
        }

    }

In the *__construct()* method, you can inject Symfony services or parameters
that the data update class needs to execute. In our case, we pass the Doctrine
entity manager to the constructor.

The *getVersion()* method is supposed to return the version string of this
update, which consists of the year, month, day, hour, minute and second. The
version allows the CampaignChain updater to execute your data update in the
right order in relation to other data update scripts.

In the *getDescription()* method, you can provide multiple lines of information
as array values, which will be displayed in the shell while your data update
routine gets executed.

The actual work is being done in the *execute()* method. This is where you can
change data in the database, move or rename files, connected to other
applications to retrieve data, etc.

Define the Data Update Service
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Essentially, data updates are `tagged Symfony services`_. Hence, the next step
is to define the service for above data update routine.

In the */Resources/config/services.yml* file of your module, add the following
lines:

.. code-block:: yaml

    acme_my_bundle.update.add_id_to_name:
        class: Acme\MyBundle\Resources\update\data\UpdateAddIdToName
        arguments:
            - '@doctrine.orm.default_entity_manager'
        tags:
            - { name: campaignchain.update.data }

What you see here is that we define a service name
*acme_my_bundle.update.add_id_to_name*. The best practice is to start with a
string that resembles the Composer package name of your module, followed by
*.update.* and then a string that resembles the name of the data update class.

Next, we define the class path of the data update class.

The *arguments* parameter is where Symfony services and parameters can be
passed to the constructor of the data update class.

Finally, you must provide the tag *campaignchain.update.data*, because only then
will your data update class be included in CampaignChain's updater.

Testing the Data Update Routine
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

To test the data update routine for your module, issue this command in the route
of your CampaignChain installation:

.. code-block:: bash

    $ php app/console campaignchain:update:data

.. note::

    Currently, downgrading data updates is not possible.


.. _entity class: http://symfony.com/doc/current/book/doctrine.html#creating-an-entity-class
.. _installed CampaignChain as explained in the README.md file: https://github.com/CampaignChain/campaignchain/blob/master/README.md#installation
.. _contact us: http://www.campaignchain.com/contact
.. _Composer package name: https://getcomposer.org/doc/04-schema.md#name
.. _Doctrine Migration Bundle: http://symfony.com/doc/current/bundles/DoctrineMigrationsBundle/index.html
.. _tagged Symfony services: http://symfony.com/doc/current/components/dependency_injection/tags.html
Sample Data
===========

It is possible to load sample data into CampaignChain, which eases the
development process.

.. warning::
    * Don't use sample data in production environments, because they might be
      buggy or contain confidential data.
    * All existing data in your CampaignChain might be wiped out. Make sure you
      backup your CampaignChain database if you are not sure whether the sample
      data you load is safe.

.. _dev-book-sample-data-packages:

Packages
--------

Sample data for CampaignChain are being made available as `Composer packages`_
and can be installed through Composer with a command such as:

.. code-block:: bash

    $ composer require amce/mydata

If you installed CampaignChain through composer with the ``--stability=dev``
option, these two default sample data packages are already available:

* `amariki/data-test`_
* `amariki/data-demo`_

The default sample data leverages the
:doc:`live development environment </developer/book/development_environment>`,
i.e. the various test accounts and instances CampaignChain, Inc. set up at
Twitter, Facebook, MailChimp, wordpress.amariki.com and other online channels.

Take a look at above packages if you'd like to create your own sample data. Some
hints:

* The data is being stored as Fixtures_.
* To have CampaignChain load your sample data, put a file ``data.yml`` into your
  bundle located at ``Resources/data/campaignchain/``.
* It's good practice to give the super user the user name ``admin`` and password
  ``test``.

Credentials
-----------

We recommend that you put all passwords, App keys, secrets, access tokens, token
secrets, refresh tokens and other security sensitive information into a
dedicated ``credentials.yml`` file. Reason being that you might want to share
the sample data with others, but not the related credentials.

The aforementioned default sample data packages ship with a template file for
credentials called ``credentials.yml.tpl``. To create your own file, follow
these instructions:

#. Rename ``credentials.yml.tpl`` to ``credentials.yml``.
#. Register your CampaignChain instance as an app for the various Channels
   listed as ``resourceOwner`` in ``credentials.yml``, such as Twitter and Facebook.
   If you've never done that, go to http://hybridauth.sourceforge.net/userguide.html
   and click on a provider (e.g. Twitter). On the respective page, there's a section
   called "Registering application". Proceed as described there.
#. Now connect a new Location in CampaignChain (e.g. a Twitter stream). When
   done, look up the respective tokens in the database table
   ``campaignchain_security_authentication_client_oauth_token`` and put them into
   ``credentials.yml``.

.. note::
    If you would like to retrieve a ``credentials.yml`` file for the default
    sample data packages that works out-of-the-box, check out how to apply for
    access to the :doc:`live development environment </open/developer/book/development_environment>`.

Usage
-----

If ``campaignchain.env`` is set to ``true`` in ``app/config/parameters.yml``,
then you will be able to load sample data into CampaignChain in its Graphical
User Interface or through a command.

To use the GUI, visit the page http://example.com/development/sample-data of
your CampaignChain installation.

.. image:: /images/developer/book/load_sample_data.png
    :width: 600px

#. Make sure you have a working ``credentials.yml`` file - see above.
#. Load the page http://example.com/development/sample-data of your CampaignChain
   installation.
#. There, pick the package of choice in the field "Data file" and select
   ``credentials.yml`` as the Include File. Activate the checkbox "Drop tables?"
   to start with a clean slate.
#. Click "Upload" and good luck :)
#. Log into CampaignChain with user ``admin`` and password ``test`` (unless
   otherwise specified by the package).

In addition to the user interface, you could also load sample data by using the
command line. Issue the following command in the root of your CampaignChain
installation to load the test data along with its credentials:

.. code-block:: bash

    $ php app/console campaignchain:fixture vendor/amariki/data-test/Resources/data/campaignchain/data.yml vendor/amariki/secrets/credentials_test.yml


Recovery
--------

Should the sample data upload not work, you can try two things:

1. Fix the sample data and reload the browser window where you tried to upload
   the sample data.
2. If 1. does not work, install CampaignChain from scratch.

.. _Composer packages: https://getcomposer.org/doc/01-basic-usage.md#composer-json-project-setup
.. _amariki/data-demo: https://github.com/Amariki/data-demo
.. _amariki/data-test: https://github.com/Amariki/data-test
.. _Fixtures: https://github.com/nelmio/alice
.. _"Commands" section for the Alice Fixtures Bundle: https://github.com/h4cc/AliceFixturesBundle/blob/master/README.md
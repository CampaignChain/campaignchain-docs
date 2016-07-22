Development Environment
=======================

CampaignChain, Inc. provides a live development environment which provides
readily available online channels to test CampaignChain modules against along
with sample data that automatically sets up CampaignChain to be used with the
development environment.

Name
----

The	fictitious company featured in the development environment is called *Amariki*.
This word was invented by Emilia, the younger daughter of Sandro Groganz, who
initiated the CampaignChain project and is the founder of CampaignChain, Inc.

Yet, no one figured out whether it means anything in one of the languages on
earth.

Online Channels
---------------

The following online channels have been set up for developers:

* http://wordpress.amariki.com (default Wordpress installation with test data)
* https://twitter.com/AmarikiTest1
* https://twitter.com/AmarikiTest2
* Facebook test user *Amariki Test One*
* Facebook test user *Amariki Test Two*
* Linkedin test user
* http://www.slideshare.net/amariki_test
* Bit.ly user *amariki*
* MailChimp user *amariki*
* GoToWebinar test user

To use these channels when developing modules for CampaignChain, you can load
ready-made sample data into CampaignChain as described below.

Sample Data
-----------

By default, CampaignChain ships with the following sample data packages if
installed with the ``--stability=dev`` option through Composer_.

* `amariki/data-test`_
* `amariki/data-demo`_

Learn :doc:`how to load sample data </ce/developer/book/sample_data>` in
CampaignChain.

.. note::
    Please contact partner@campaignchain.com to retrieve a ``credentials.yml``
    file that works out-of-the-box with above data packages and the development
    environment.

Test Emails
-----------

We have test email accounts for above test online channels. For example, as an
account email to receive notifications from Twitter or a recipient email to
send MailChimp newsletters to.

.. note::
    Please contact partner@campaignchain.com to apply for access to the email
    inbox where we collect all incoming test emails and to retrieve a list of
    available test emails.


.. _Composer: https://getcomposer.org
.. _amariki/data-demo: https://github.com/Amariki/data-demo
.. _amariki/data-test: https://github.com/Amariki/data-test
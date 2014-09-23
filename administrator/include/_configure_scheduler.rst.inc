The CampaignChain scheduler is a PHP script that executes scheduled Operations.

On Linux or Mac OS X, configure it as a `cron job`_ so that it runs automatically
every minute:

.. code-block:: bash

    $ crontab -e -u <username>
    */1 * * * * /usr/bin/php /path/to/symfony2/app/console campaignchain:scheduler

On Windows, you could use the `task scheduler or AT command`_ to achieve the same.

.. _cron job: http://en.wikipedia.org/wiki/Cron
.. _task scheduler or AT command: http://technet.microsoft.com/en-us/library/bb726974.aspx
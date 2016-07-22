CampaignChain's CTA tracking mechanism uses Bitly to shorten URLs that contain
the tracking ID.

Please request a Bitly access token here: https://bitly.com/a/oauth_apps

Next, open the file *app/config/config.yml* in CampaignChain and replace
``insert_here_you_bitly_access_token`` with the access token you requested.

.. code-block:: yaml

    # app/config/config.yml
    hpatoio_bitly:
        access_token: insert_here_your_bitly_access_token
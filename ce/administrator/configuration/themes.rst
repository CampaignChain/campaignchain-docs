Themes
======

The look & feel of CampaignChain can be configured as follows.

Layout
~~~~~~

CampaignChain lets you configure various parts of the layout. For example,
whether you want to show the header and footer of the graphical user interface.
This comes handy if you want to omit them to embed CampaignChain through an
iFrame.

The standard configuration of CampaignChain supports two layouts:

* default
* embedded

You can find the respective configuration in the `config.yml` file of the core
bundle:

.. code-block:: yaml

    campaignchain_core:
        theme:
            layouts:
                default:
                    show_header: true
                    show_footer: true
                embedded:
                    show_header: false
                    show_footer: false

To enable a specific layout, call a page in CampaignChain with the
`campaignchain-layout` URL parameter. For example:

`http://www.mycampaignchain.com/?campaignchain-layout=embedded`

The setting will be applied to all subsequent pages. If you want to go back
to the default view, simply switch by calling:

`http://www.mycampaignchain.com/?campaignchain-layout=default`
CampaignChain Documentation Standards
=====================================

Symfony Documentation Standards
-------------------------------
CampaignChain documentation follows the `documentation standards of the Symfony project`_.

Additional Conventions
----------------------
CampaignChain documentation also follows these additional conventions.

1. When referring to an CampaignChain entity, you should start the entity name with
   a capital letter. For example, you should use "Channel module" instead of
   "channel module". This makes it clear that you are referring to a specific
   entity and not a generic channel, location, activity, operation, hook or
   milestone concept.

2. All file names and directory paths are italicized. You should always
   include a trailing slash on directory paths. For example,
   *public/images/icons/16x16/linkedin.png* refers to a file name and
   *your-project/src/* refers to a directory path.

3. When referring to key or parameters names in configuration files, those
   names should be italicized. However, when referring to the corresponding
   values, you should enclose those values in single quotes. For example, the
   parameter *foo* and the value 'bar'.

4. CampaignChain documentation favors using :: shorthand for PHP code blocks and
   code-block:: syntax for other code blocks. For example:

  ::
  
    ::
      <?php
      // PHP code block
      $wizard = $this->get('campaignchain.core.channel.wizard');
      $wizard->setName($profile->displayName);
      $wizard->addLocation($location->getIdentifier(), $location);
      $channel = $wizard->persist();
      $wizard->end();
  
    .. code-block::yaml

      # YAML code block
      acme_campaignchain_channel_linkedin_create:
        pattern:  /channel/linkedin/create
        defaults: { _controller: AcmeCampaignChainChannelLinkedInBundle:LinkedIn:create }

5. CampaignChain documentation calls out pieces of key information using note:: and
   tip:: specific admonitions. For example:

  ::

   .. note:: 
      This is something important.

6. Images should be created in `LibreOffice Draw`_. Please provide the original
   *.odg* files in the */images/* directory along with the related PNG file.



.. _documentation standards of the Symfony project: http://symfony.com/doc/current/contributing/documentation/standards.html
.. _Symfony configuration blocks: http://symfony.com/doc/current/contributing/documentation/format.html#docs-configuration-blocks
.. _LibreOffice Draw: http://www.libreoffice.org/discover/draw/
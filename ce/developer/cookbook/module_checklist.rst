Checklist for Developing Modules
================================

- Make sure the GUI uses only Bootstrap components, CSS and JS. Where applicable,
  use the `Braincrafted Boostrap components`_.
- Add license information and copyright notice on top of each file in your module.
- Did you remove all unnecessary files which have been automatically created by
  the module generator (e.g. *Controller/Default.php*, *Resources/doc*)?
- Test against the sample data and first of all, make sure that it gets loaded
  properly.
- Update the sample data if applicable and in a respective feature or release
  branch.
- Make sure each module ships with `schema and data update routines`_.
- Reset the system and install again to test whether the new feature breaks
  anything.
- Please `contact us`_ to add newly released modules to the `modules store`_.

.. _Braincrafted Boostrap components: http://bootstrap.braincrafted.com/components.html
.. _schema and data update routines: :doc:`module_update`
.. _contact us: http://www.campaignchain.com/contact
.. _modules store: https://github.com/store-campaignchain-com/store-campaignchain-com.github.io
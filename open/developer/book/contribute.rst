Contributing to CampaignChain
=============================

If you would like to add new functionality or fix a bug in CampaignChain, you
are more than welcomed!

In general, we follow the best practices of open-source collaboration and
developed some of our own - which is mostly due to the fact that CampaignChain
is highly modular.

Find below some guidelines and we'd appreciate if you followed them. Should you
have questions, please `contact us`_.

Symfony
-------

We closely follow the contribution guidelines of the Symfony project. Please
make yourself acquainted with:

* `Coding standards`_
* `Code conventions`_

GitHub
------

We use `GitHub`_ to develop the CampaignChain Open Edition. It allows us to
collaborate with developers world-wide.

Please follow these guidelines:

Issues
~~~~~~

Always create an issue for the task you are working on at https://github.com/CampaignChain/campaignchain-custom/issues.

Commit Message
~~~~~~~~~~~~~~

The Git commit message should point to the issue you are working on. The syntax
is:

.. code-block::

    CampaignChain/campaignchain#{issue-number} {issue-title}

In `PHPStorm`_, you can use below definition
for the commit message field when configuring the GitHub server to retrieve
issues within PHPStorm:

.. code-block::

    CampaignChain/{project}#{number} {summary}

Pull Requests
~~~~~~~~~~~~~

Never commit directly to the ``master`` branch of CampaignChain or its modules.
Instead, please :ref:`create branches <dev-book-contribute-branching>`. That way
we can first test your contributions in the branch, ask you for changes, and
then merge them with the ``master`` branch.

What's great about GitHub is that it `let's you easily create pull requests`_
and then comment on it, `even on single lines of the code`_.

So, once you are done with your changes and they are all committed to your
branch, please create a pull request and we'll review it.

.. _dev-book-contribute-branching:

Branching
---------

Whenever you create a new feature for CampaignChain or want to contribute a bug
fix, please create a new branch of the respective CampaignChain module(s) or
Symfony bundles you are working on.

Also, make sure you create a new branch of the `CampaignChain/campaignchain`_
application as well.

How to Create a Branch?
~~~~~~~~~~~~~~~~~~~~~~~

If you are not familiar with Git and branching, please read the introduction
`Basic Branching and Merging`_.

The name of the branch should include ``campaignchain-`` and the number of the
related issue, such as ``campaignchain-42``.

Inline Alias in composer.json
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

You can define in the ```composer.json```_(https://github.com/CampaignChain/campaignchain/blob/master/composer.json)
file of the application, which branched modules/bundles you'd like to use for
development. Just list them in the ``require-dev`` section and define the
branch as a `Composer inline alias`_.

Here's an example how to do it for your custom module/bundle:

.. code-block:: yaml
    "require-dev": {
        "acme/my-bundle": "my-branch as dev-master"
    },

If you are working on existing CampaignChain modules, e.g. to fix a bug, create
a branch and define it as an inline alias. All `Composer version constraints`_
defined elsewhere will be overridden.

.. code-block:: yaml
    "require-dev": {
        "campaignchain/core": "my-branch as dev-master"
    },

Modify Sample Data
~~~~~~~~~~~~~~~~~~

Please modify the :ref:`sample data <dev-book-contribute-sample-data>` accordingly
by changing existing fixtures or by adding those which allow others to test new
features.

Branching Model
~~~~~~~~~~~~~~~

We structure the flow of our development às follows:

* The ``master`` branch holds the latest stable code.
* New features are being developed in separate branches.
* Release branches hold the code of the tagged ``master` branch.

.. _dev-book-contribute-sample-data:

Sample Data
-----------

When you are developing with CampaignChain, sample data will be available
automatically. Learn how to :doc:`import sample data to the system </open/developer/book/sample_data>`.

To allow testing of your changes by others, please keep all the publicly available
:ref:`sample data packages <dev-book-sample-data-packages>` in sync with your
branch.

License
-------

All code developed for the CampaignChain Open Edition is available under the
`Apache License`_. We ask all
contributors to assign new code to the same license.

Please add a ``LICENSE`` file with the `content of the Apache License`_ into the
root of new packages that you want to be included as part of the CampaignChain
Open Edition.

The below license block has to be present at the top of every file.

In PHP before the namespace:

.. code-block:: php

    /*
     * Copyright 2016 CampaignChain, Inc. <info@campaignchain.com>
     *
     * Licensed under the Apache License, Version 2.0 (the "License");
     * you may not use this file except in compliance with the License.
     * You may obtain a copy of the License at
     *
     *    http://www.apache.org/licenses/LICENSE-2.0
     *
     * Unless required by applicable law or agreed to in writing, software
     * distributed under the License is distributed on an "AS IS" BASIS,
     * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
     * See the License for the specific language governing permissions and
     * limitations under the License.
     */

In ``.yml`` configuration files, at the very top:

.. code-block:: yaml

    # Copyright 2016 CampaignChain, Inc. <info@campaignchain.com>
    #
    # Licensed under the Apache License, Version 2.0 (the "License");
    # you may not use this file except in compliance with the License.
    # You may obtain a copy of the License at
    #
    #    http://www.apache.org/licenses/LICENSE-2.0
    #
    # Unless required by applicable law or agreed to in writing, software
    # distributed under the License is distributed on an "AS IS" BASIS,
    # WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    # See the License for the specific language governing permissions and
    # limitations under the License.

In TWIG files at the very top:

.. code-block:: html+jinja

    {#
    Copyright 2016 CampaignChain, Inc. <info@campaignchain.com>

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
    #}

In CSS files at the very top:

.. code-block:: css

    /*
    Copyright 2016 CampaignChain, Inc. <info@campaignchain.com>

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
    */

Credits
-------

If you use third-party intellectual property, you must make sure that you are
allowed to do so. Please add a ``NOTICE`` file in the root directory of a new
module/bundle where you credit the copyright holders. See for example the
`NOTICE file of the core bundle`_.

.. _GitHub: http://www.github.com
.. _contact us: http://www.campaignchain.com/contact/
.. _Coding standards: http://symfony.com/doc/current/contributing/code/standards.html
.. _Code conventions: http://symfony.com/doc/current/contributing/code/conventions.html
.. _PHPStorm: https://www.jetbrains.com/phpstorm/
.. _let's you easily create pull requests: https://help.github.com/articles/creating-a-pull-request/
.. _even on single lines of the code: https://help.github.com/articles/commenting-on-differences-between-files/
.. _CampaignChain/campaignchain: https://github.com/CampaignChain/campaignchain
.. _Basic Branching and Merging: https://git-scm.com/book/en/v2/Git-Branching-Basic-Branching-and-Merging
.. _Composer inline alias: https://getcomposer.org/doc/articles/aliases.md#require-inline-alias
.. _Composer version constraints: https://getcomposer.org/doc/articles/versions.md
.. _Apache License: http://www.apache.org/licenses/LICENSE-2.0
.. _content of the Apache License: http://www.apache.org/licenses/LICENSE-2.0
.. _NOTICE file of the core bundle: https://github.com/CampaignChain/core/blob/master/NOTICE
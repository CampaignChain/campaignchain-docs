How to Use the REST API
=======================

This tutorial teaches you how to make use of the built-in REST API available for
CampaignChain.

Scenario
--------

#. User navigates to landing page.
#. Get ongoing and upcoming scheduled campaigns and display to user to select.
#. Get CC users and display to user to select.
#. User provides a publishing date (cannot be prior to now).
#. Ensure that publishing date is within campaign duration.
#. User saves page.
#. System retrieves Channel by URL and module URI (should be done in advance and by storing channel ID).
#. System creates new Activity by providing Channel ID, Activity, assignee and Location data.
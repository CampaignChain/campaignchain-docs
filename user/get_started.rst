Get Started
===========

This is a brief step-by-step guide on how to create your first marketing
Campaign and Activity within CampaignChain. You will learn how to connect
Twitter as a Channel and how to post a Tweet on the stream of the related
Twitter user account.

.. _Connect to a Location:

1. Connect to a Location
------------------------

To show you how to connect a new Location, we'll use Twitter as an example. To
connect a Twitter Location with CampaignChain, click the *Create New* button in
the header menu and choose *Location*.

.. image:: /images/user/create_new_location.png
    :width: 600px

On the next screen, select Twitter as the Channel and click *Next*.

.. image:: /images/user/select_new_twitter_location.png
    :width: 600px


.. note::

    Should you now see the *Provide Application Credentials* screen, then please
    see :ref:`how to create new OAuth Apps <create-new-oauth-apps>`.

When clicking the button *Connect with Twitter*, the login screen for Twitter
will be displayed to you. Please enter your Twitter user name and your Twitter
password.

.. image:: /images/user/twitter_channel_login.png
    :width: 600px

If Twitter accepted your credentials, the stream of the Twitter user you
logged in as will now be available as a Channel Location within
CampaignChain.

2. Create a Campaign
--------------------

An Activity such as posting on Twitter can only be created from within a
Campaign. Click the *Create New* button in the header and choose
*Campaign*.

.. image:: /images/user/create_new_campaign.png
    :width: 600px

Select the campaign type *Scheduled Campaign* and proceed with *Next*.

.. image:: /images/user/select_scheduled_campaign.png
    :width: 600px

Fill in the fields to populate your new Campaign with data, such as:

- *Name*: An arbitrary name of your Campaign, e.g. "Launch of new product"
- *Timezone*: The timezone of the Campaign. For international marketing teams,
  the best choice is *UTC*.
- *Duration*: Pick the start and end date of your Campaign.
- *Assignee*: The person in your team responsible for the Campaign.

Click *Save* and your first Campaign will be created.

.. image:: /images/user/create_new_campaign_form.png
    :width: 600px

If you now click *Plan* in the header navigation, you will see your new
Campaign in the Timeline.

.. image:: /images/user/timeline.png
    :width: 600px

3. Create an Activity
---------------------

Now you are ready to create your fist Activity, which will be posting a status 
update on Twitter.

Click the *Create New* button in the header and choose *Activity*.

.. image:: /images/user/create_new_activity.png
    :width: 600px

In the next screen, select your newly created Campaign and in the *Location*
field, pick the Twitter user stream you just connected to.

Once you have selected the Location, a new field will appear which allows you
to select the Activity you want to perform within the Location. Here, choose
*Update Status* and click *Next*.

.. image:: /images/user/create_new_activity_form.png
    :width: 600px

A form will appear and prompt you to insert the following data:

- *Activity Name*: An arbitrary name that will be used within CampaignChain. For
  example, "Initial announcement".
- *Twitter Message*: This is the text that will appear on Twitter, e.g. "Try
  our new product, it's awesome: \http://www.example.com/newproduct"
- *Due*: Here, you can schedule the tweet to be posted at a specific date and
  time.
- *Assignee*: Define who is responsible for taking care of this Tweet.

.. image:: /images/user/new_twitter_status_update_form.png
    :width: 600px

That's it! If you now click *Plan* again, you will see the new Activity as
part of your new Campaign.
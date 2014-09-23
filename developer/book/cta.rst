Call to Action (CTA) Tracking
=============================

This section describes the inner workings of CampaignChain's Call to Action Tracking.
The provided information is useful for anyone developing Operation modules with
CampaignChain or for those configuring third-party channels to work with
CampaignChain.

What is a CTA?
~~~~~~~~~~~~~~

    In web design, a CTA is a banner, button, or some type of graphic or text
    on a website meant to prompt a user to click it and continue down a
    conversion funnel. It is an essential part of inbound marketing as well
    as permission marketing in that it actively strives to convert a user
    into a lead and later into a customer.

    -- `Wikipedia`_

In CampaignChain, a CTA is essentially a URL that appears in a HTML href link or
form action. It appears within an Operation and each Operation can contain 0 to
many CTAs. For example, a tweet could include various links that CampaignChain treats
as CTAs, while a Google Ad would contain only 1 link as the CTA.

Tracking ID
~~~~~~~~~~~

CampaignChain leverages two types of IDs for its CTA tracking:

- *CTA Tracking ID*: Each CTA has a unique ID assigned by CampaignChain per URL that
  is included in an Operation. If you read about just the Tracking ID in the
  documentation, then it's referring to the CTA Tracking ID.
- *Channel Tracking ID*: For each Channel that has been connected with CampaignChain,
  a unique ID will be generated. This ID must be provided in the tracking code
  that is being included in a Channel. When the tracking code is activated,
  CampaignChain checks whether the provided Channel Tracking ID exists and whether the
  tracking code has been executed from a URL that actually resides within the
  Channel.

Tracking Process
~~~~~~~~~~~~~~~~

To make CTA tracking work, a Channel that is connected with CampaignChain provides
the relevant information to CampaignChain for tracking the CTA path
that is part of a conversion funnel.

High-level View
...............

From a 30,000-feet perspective, this is how the tracking process works:

1. A link or form inside an Operation acts as the initial CTA at the beginning
   of a marketing funnel. The initial CTA contains a unique Tracking
   ID which allows CampaignChain to trace back the link to the respective Actions
   and Media (Campaign, Activity, Operation, Location, etc.). For example,
   a Twitter post that links to a landing page within a website.
2. All subsequent Locations inside a connected Channel ping CampaignChain and let it
   know through the Tracking ID that the respective Location was referred by a
   CTA.

The communication between CampaignChain and a Channel is achieved through JavaScript
included in the Channel that posts the CTA information to CampaignChain and
optionally also through REST-based communication between CampaignChain and the
Channel. Depending on the depth of integration between CampaignChain and a Channel,
there are 3 different types of tracking (described in subsequent sections).

In-depth Flow Description
.........................

The single steps of the CTA tracking process are as follows:

\1. The Operation's content gets parsed for links right before execution.

\2. If the Operation contains 1 or more links, the following happens:

\2.1. A unique Tracking ID gets assigned to each URL, no matter if an
Operation contains the same URLs multiple times.

.. note::
    An Operation could well contain the same URL multiple times, For example,
    a banner image on a landing page could point to the same URL in its key
    visual as well as a button that is part of the banner. When analyzing the
    effectiveness of the banner image, you want to know whether the key visual
    or the button caused more clicks. That's why each of them gets treated as a
    unique CTA with its own Tracking ID, although they have the same URL.

\2.2. The Tracking ID gets appended to the URLs found inside the Operation.

\2.2.1. If it is a full URL, then append the Tracking ID and
replace the original URL with a shortened URL (CampaignChain uses `Bit.ly`_ by default).

\2.2.2. If the URL is already shortened, expand it, append the
Tracking ID and replace the original shortened URL with a new shortened
URL.

\2.3. For each link, an entry is made in the CTA table with the Tracking
ID and the related Operation as well as the original URL (full and short, if
the latter was provided).

\3. CampaignChain executes the Operation that now contains the new short URLs with
the Tracking ID, e.g. it publishes a status update on Twitter that contains a
link to a landing page.

\4. When someone activates a CTA, e.g. clicks a link in a Tweet published by
CampaignChain, the URL points to a Location. If that Location is part of a Channel
that includes the tracking code and is connected with CampaignChain, then the
following happens:

\4.1. The tracking code checks whether the URL that pointed to the current page
includes the Tracking ID. If yes, then it proceeds. If not, then it exits.

\4.2. If the Tracking ID exists, the Tracking code sends this information to
CampaignChain: Channel Tracking ID, CTA Tracking ID, URL of current Location, URL of
target Location and additional information useful for monitoring.

\4.3. CampaignChain checks whether the Channel Tracking ID is valid, i.e. if the
Channel sending the tracking data is actually connected with CampaignChain.

\4.3.1. If yes, then it performs some validity checks on the data, most notably
whether the Tracking ID exists within CampaignChain, and finally saves the tracking
data for monitoring purposes.

\4.3.2. If no, then it will not save the data and instead notify the admin of
an error (most likely, the Tracking Code has been included in a Channel that
has not been connected with CampaignChain yet or this is a Denial of Service
attack).

\4.4. While CampaignChain processes the tracking data, the tracking code in the
Channel appends the Tracking ID to the target URL (if another one does not exist
yet, because the target URL is part of a new Operation) or saves it in a cookie.
It then redirects the visitor to the target Location.

.. note::

    Passing on the Tracking ID enables CampaignChain to do two things:

    * Understand, whether e.g. the visitor browses a website away from a landing
      page before coming back to it and activating a CTA that leads to another
      Operation.

    * Track the effectiveness of Operations across Channels.

Types of Tracking
~~~~~~~~~~~~~~~~~

To track CTAs, different types of tracking are used with CampaignChain to
monitor the inbound marketing funnel.

CampaignChain-to-Channel (unidirectional)
.........................................

* *Integration level:* Useful if CTA is under control, but not the Channel.
* *Example:* We can add a Tracking ID to a link that will be published on
  Twitter, but we cannot install something on Twitter to establish a
  connection between Twitter and CampaignChain to exchange information.
* *Tracking ID:* The Tracking ID must be included in the CTA. It is
  important, because it helps to distinguish between Campaigns and Activities
  if e.g. the same Landing Page is being used as a CTA target within the same
  Campaign various times or in different campaigns.
* *Pros:* Simple to implement by adding the Tracking ID to the URL of the
  CTA.
* *Cons:* Ideally, CampaignChain would be in control of the Operation (e.g. posting
  to Twitter from within CampaignChain). If not possible, then a user would have to
  manually append the Tracking ID.

Channel-to-CampaignChain (unidirectional)
.........................................

* *Integration level:* The channel sends information about the Operation,
  Location and CTA to CampaignChain.
* *Example:* A JavaScript snippet included in Wordpress sends information to
  CampaignChain about a link's URL that was clicked inside a blog post, as well as
  the URL of the blog entry, etc.
* *Tracking ID:* At least the Tracking ID of the initial CTA should be
  available. Then CampaignChain is able to match the CTA's URL provided by the
  Channel with the Campaign and Activity it belongs to. Information about the
  source and target Location is also provided by the Channel for CampaignChain to
  easily map the related URLs to the Locations inside CampaignChain.
* *Pros:* This approach has the security advantage that the third-party application
  is in control of the communication towards CampaignChain.
* *Cons:* There must be a mechanism inside the Channel that ensures that at
  least the Tracking ID of the initial CTA is being carried on to the target
  Location.

CampaignChain-to-Channel (bidirectional)
........................................

* *Integration level:* CampaignChain and the Channel are tightly integrated when it
  comes to creating Operations and Locations, thus providing maximum
  communication between the two when it comes to CTA tracking.
* *Example:* A landing page has been created within Wordpress. With CampaignChain
  connected to Wordpress (e.g. through a REST API), CampaignChain grabs the content
  of the Wordpress page, parses it, stores the CTAs the page includes and
  makes the page public at the scheduled time. As in the unidirectional
  Channel-to-CampaignChain approach, a JavaScript snippet inside Wordpress sends
  information to CampaignChain once the CTA gets activated.
* *Tracking ID:* CampaignChain can pass all Tracking IDs for the CTAs in a Location
  to the Channel to be appended to each respective URL inside a Location for
  more granular tracking.
* *Pros:* The tighter coupling allows for more granular tracking, i.e. it is
  possible for CampaignChain to identify not just a Location, but also the Operation
  that includes a triggered CTA. Also, this approach has the performance
  advantage that the Channel as well as CampaignChain can handle the tracking more
  efficiently, because both are aware of all relevant information.
* *Cons:* Creating the tighter integration requires a higher investment in terms of
  time and money.


.. _Wikipedia: http://en.wikipedia.org/wiki/Call_to_action_%28marketing%29
.. _Bit.ly: http://dev.bitly.com
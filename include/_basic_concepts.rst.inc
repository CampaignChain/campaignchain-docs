Basic Concepts
--------------
CampaignChain's software architecture has been designed along digital marketing
terms and concepts in a specialized way, so this section gets you up to speed
on CampaignChain's terminology and explains the main entities to you.

CampaignChain knows two types of entities, a Medium and an Action, which are:

+-------------+-------------+
| Medium      | Action      |
+=============+=============+
| * Channel   | * Campaign  |
| * Location  | * Milestone |
|             | * Activity  |
|             | * Operation |
+-------------+-------------+

Campaigns
~~~~~~~~~

**Campaigns** are at the core of CampaignChain, and are the "DNA of modern digital
marketing"[1]_. In CampaignChain, every campaign uses one or more communication
**channels**. Campaigns also have **milestones** and **activities**.

Campaigns usually come in two variants: **manually scheduled campaigns**,
which have a defined start and end date, and **triggered campaigns**
(also called nurtured campaigns), which occur in response to user events.
A campaign focused on a new product launch is an example of the former,
whereas a drip email campaign that begins when a user fills up a registration
form is an example of the latter.

Channels & Locations
~~~~~~~~~~~~~~~~~~~~

Campaigns use online **channels**, which are the pathways by which campaign
content reaches its audience. Common examples of channels include websites,
blogs and social networks like Facebook and LinkedIn. For monitoring purposes,
CampaignChain also allows connections to channels to retrieve traffic statistics
(e.g. Google or YouTube Analytics) and lead generation data maintained in a CRM.

Every channel includes one or more **locations**, which allow granular publishing
of campaign content. For example, a Twitter channel has only one location: the
Twitter stream. However, a website channel might have various locations: a
landing page, a banner on the home page, a "Contact Us" page with a form,
and so on. Similarly, a LinkedIn channel might consist of two locations:
a company profile page and a news stream. Locations are being created when
connecting to a new Channel.

Furthermore, Locations can be created by an Operation. For example, an Operation
that posts a Tweet on a Twitter stream is essentially creating a new Location
(i.e. that Tweet) within a Location (i.e. a Twitter user's stream). Learn more
about Operations below.

Milestones
~~~~~~~~~~

**Milestones** are key events or reference points during a campaign. For
example, the campaign go-live date could be a milestone, and a press tour
could be a second milestone. When you set up campaign milestones, related
actions can be defined. For example, you could compare analytics data between
two milestones. Or you could notify a member of your marketing team to start
working on the next set of tasks once a milestone has been reached.

Activities and Operations
~~~~~~~~~~~~~~~~~~~~~~~~~

Every location allows one or more **activities** which can be undertaken.
For example, creating a new post is an example of an activity for a blog
channel.

Every activity must always have at least one **operation**. For example,
posting on Twitter is one activity which equals the operation.

In other cases, a single activity may encompass multiple operations. For
example, defining and creating a Google AdWords campaign that runs for 3
months is a possible activity for the Google AdWords channel. However,
this activity could consist of two operations: the first operation might
be a Google Ad that runs for the first 2 months of the campaign, and the
second operation would be a second, different Google Ad that runs for the
remaining 4 weeks.
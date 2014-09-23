:orphan:

Glossary
========

.. glossary::
    :sorted:

    Activity 
      Every location allows one or more Activities which can be undertaken.
      For example, creating a new post is an example of an Activity for a 
      blog Channel.
      
    Campaign
      Campaigns are a series of marketing operations utilizing one or more 
      communication channels. Campaigns have Milestones and Activities.

    Channel 
      Campaigns use online channels, which are the pathways by which 
      campaign content reaches its audience. Common examples of Channels
      include websites, blogs and social networks like Facebook and LinkedIn.  
     
    Hook
      A Hook is a reusable component that provide common functionality and 
      can be used across modules to configure Campaigns, Milestones, Channels, 
      Locations, Activities and Operations.
      
    Location
      Every Channel includes one or more Locations, which allow granular 
      publishing of campaign content. For example, for a Twitter Channel, 
      the Twitter stream is a Location. 

    Milestone
      Milestones are key events or reference points during a Campaign. 
      For example, the campaign go-live date could be a Milestone, and a
      press tour could be a second Milestone. 
    
    Module
      A module is a pre-packaged set of functionality. In CampaignChain, modules
      are developed as Symfony bundles, with additional configuration that 
      allows CampaignChain to load them into its system.
      
    Operation
      Every Activity must always have at least one Operation. For example, 
      posting on Twitter is one Activity which equals the Operation. 

    GUI
        Graphical User Interface

    Tracking ID
        Each Call to Action has a unique Tracking ID assigned by CampaignChain
        which enables CampaignChain to match a URL clicked in a Channel to a
        Location specified inside CampaignChain.

    CTA
        Call to Action
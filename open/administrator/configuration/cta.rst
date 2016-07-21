Call to Action Configuration
============================

To enable :ref:`CTA tracking <dev-book-overview-cta>` for a Channel, follow these steps:

1. Connect Trackable Channel
----------------------------

In the CampaignChain header menu, click the *Create New* button and select a
*Location* that allows you to add the tracking JavaScript code provided by
CampaignChain.

.. image:: /images/user/create_new_location.png
    :width: 600px

Choose the appropriate Location from the drop-down list, e.g. *Website* to
include a Website into CTA tracking.

.. image:: /images/administrator/select_new_website_location.png
    :width: 600px

Fill in the required data to connect the Channel. For example, provide the
base URL of a Website (you can omit adding pages of the Website).

.. image:: /images/administrator/connect_new_website_channel.png
    :width: 600px

2. Include Tracking Code
------------------------

Once you're done with connecting a trackable Channel, CampaignChain will display
a list of connected Channels to you. This list will include a button to enable
CTA tracking for trackable Channels.

.. image:: /images/administrator/channels_list.png
:width: 600px

Clicking on such button will display a page with instructions to include the
tracking snippet.

.. image:: /images/administrator/enable_cta_tracking.png
:width: 600px

2.1 Directly within HMTL Source Code
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

If you own the Channel you plan to include and you also have full control
to directly manipulate the HTML source, then you can include the JavaScript
snippet provided on the "Enable CTA Tracking" page.

Include the snippet by adding the code to your Channel, ideally
right before the closing body element (i.e. *</body>* element) and make sure that
it appears on all pages of the Channel.

2.2 Use Google Tag Manager
~~~~~~~~~~~~~~~~~~~~~~~~~~

In case you can't access the Channel or instead of waiting months for someon else
to update the code of a Channel, Google Tag Manager (GTM) comes to the rescue. It 
lets you launch new tags with just a few clicks. GTM supports container snippets,
a small piece of JavaScript or non-JavaScript code that it includes into your pages.

Google Tag Manager allows you to create a new *Custom HTML Tag* at the `GTM Web 
interface`_. Paste the CampaignChain tracking code into the *HMTL* section. Make 
sure the event is fired on all pages. The last step  is to publish your new tag in
GTM.

3. Anonymizing or Branding the Tracking Script
----------------------------------------------

If you want to hide from visitors to your CTA-tracked Channel, that you are
using CampaignChain or you want to custom brand the tracking code, then we have
configuration options for you.

One is in the *app/config/parameters.yml* file:

.. code-block:: yaml

    parameters:
        campaignchain.tracking.js_route: /tracking.js

The URL of the tracking script itself can be changed with
*campaignchain.tracking.js_route*. There you defined the path aka URI to the
script relative to the base URL where CampaignChain is installed.

.. warning::

    We recommend to not change the route after you started using CampaignChain.
    If you have to for whatever reason, be aware that it affects all Channels
    that include the tracking snippet. They would have to adjust the path to
    the tracking script in said snippet.

The other relevant configuration options can be found in
*app/config/config_campaignchain_bundles.yml*:

.. code-block:: yaml

    campaignchain_core:
        tracking:
            id_name: cctid
            js_mode: prod
            js_class: CCTracking
            js_init: cc

With *campaignchain_core.tracking.id_name*, you can define the name of the URL
parameter which CampaignChain attaches to links pointing to a connected channel.
Make sure the name you choose is short and as unique as possible, to avoid that
it collides with other parameters that might already be in the URL.

.. warning::

    Never change the ``id_name`` after you started using CampaignChain, because
    previous tracking data might get lost and there are unforeseeable side-effects
    with upcoming changes to the functionality.

The name of the JavaScript class that appears inside the tracking script can
be customized with the *campaignchain_core.tracking.js_class* parameter.

Finally, *campaignchain_core.tracking.js_init* allows you to define the name of the
JavaScript function that is being called to pass the Channel ID in the tracking
code.

.. warning::

    As with the route, we recommend to not change it after you started using
    CampaignChain, for the very same reasons.

When accessed through the Symfony production environment (i.e. */app.php*), then
the tracking script will automatically be minimized/obfuscated. This is how it
looks then with the default configuration parameters explained above:

.. code-block:: js

    eval(function(p,a,c,k,e,d){e=function(c){return(c<a?'':e(parseInt(c/a)))+((c=c%a)>35?String.fromCharCode(c+29):c.toString(36))};if(!''.replace(/^/,String)){while(c--){d[e(c)]=k[c]||e(c)}k=[function(e){return d[e]}];e=function(){return'\\w+'};c=1};while(c--){if(k[c]){p=p.replace(new RegExp('\\b'+e(c)+'\\b','g'),k[c])}}return p}('(d(){d Y(S){m z=H.1C("z");z.1D=S;z.1E="1F/1B";H.1A.1w(z)}6(1x p==="1y"){Y("//F.1z.1l/F/p/1G-1.11.1.1j.G")}Y("//1H.1O.1l/F/1v/G-V/2.1.2/G.V.1j.G");d q(){3.8="1Q";3.e=O;3.A=O;3.u=i.o.w;3.4="5-c";3.18="/1R/1N/1M/1I/K";6(3.4=="5"||3.4=="5-c"){b.9("3.8 = "+3.8)}}q.y.14=d(7){3.7=7;6(3.17()){6(3.4=="5"||3.4=="5-c"){b.9("s t B v r.")}6(3.4=="5"||3.4=="5-c"){m N="/1J.1K"}j{m N=""}m E="1L://1S.0.0.1:1u"+N+3.18+"/"+3.A;6(3.4=="5"||3.4=="5-c"){b.9("1p r: "+E)}p.F({S:E,I:{1o:3.8,1t:3.e,u:3.u,7:3.7},1r:"1q",1s:U,1n:3,1P:1Z,12:d(I,D){6(I.12){3.1c(I.2k)}6(3.4!="5-c"){i.o.w=3.7}j{b.9("1m 12: "+D);b.9("2l 2m R: "+3.7)}},1k:d(1h,2j,1f){6(3.4=="5-c"){b.9("1m 1k: r: "+E+", D: "+1h.D+", 2i: "+1f)}j{i.o.w=3.7}}})}j{6(3.4=="5"||3.4=="5-c"){b.9("2e s t 2f.")}i.o.w=3.7}};q.y.17=d(){m h="2g s t W Q \'"+3.8+"\'";6(3.u.10().f(3.8)<0){h=h+"B 1d v r";3.e=3.1g();6(3.e){h=h+", 2h B v Z."}j{h=h+" P B 1d v Z."}}j{3.e=1T((K 2o("[?|&]"+3.8+"="+"([^&;]+?)(&|#|;|$)").2t(3.u)||[,""])[1].2r(/\\+/g,"%20"))||O;h=h+" B v r."}6(3.4=="5"||3.4=="5-c"){b.9(h);b.9("s t L: "+3.e)}x 3.e};q.y.1c=d(n){6(3.7.10().f(3.8)>=0){x 13}2q(n){M"2p":J.2s(3.8,3.e);6(3.4=="5"||3.4=="5-c"){b.9(\'2n v V: s t W n "\'+n+\'", Q "\'+3.8+\'" P L "\'+3.e+\'".\')}15;M"2d":6(3.7.f(3.8+"=")>=0){m 1e=3.7.C(0,3.7.f(3.8));m l=3.7.C(3.7.f(3.8));l=l.C(l.f("=")+1);l=(l.f("&")>=0)?l.C(l.f("&")):"";3.7=1e+3.8+"="+3.e+l}j{6(3.7.f("?")<0)3.7+="?"+3.8+"="+3.e;j 3.7+="&"+3.8+"="+3.e}6(3.4=="5"||3.4=="5-c"){b.9(\'21 R r: s t W n "\'+n+\'", Q "\'+3.8+\'" P L "\'+3.e+\'".\')}15;M"1Y":6(3.4=="5"||3.4=="5-c"){b.9(\'1X 7 r "\'+3.7+\'" 1V R n "\'+n+\'".\')}15}};q.y.1g=d(){x J.1W(3.8)};q.y.1a=d(){6(3.u.10().f(3.8)>=0){6(H.19.f(o.23+"//"+o.24)!==0){J.2a(3.8);6(3.4=="5"||3.4=="5-c"){b.9("29 16.");b.9("Z 28.")}x 13}}6(3.4=="5"||3.4=="5-c"){b.9("25 a K 16.");b.9("26: "+H.19)}x U};i["T"]=i["T"]||d(X){6(i.p&&i.J){m k=K q();k.A=X;6(k.4=="5"||k.4=="5-c"){b.9("3.A = "+k.A)}6(k.1a()===13){k.14(i.o.w)}6(k.4=="5-c"){p("a").27("1i",d(1b){1b.2b()})}p("a").1i(d(){k.14(p(3).1U("w"));x U})}j{22(d(){i["T"](X)},2c)}}})();',62,154,'|||this|mode|dev|if|target|idName|log||console|stay|function|idValue|indexOf||logMsg|window|else|tracker|suffix|var|affiliation|location|jQuery|CCTracking|URL|Tracking|ID|source|in|href|return|prototype|script|channel|is|substring|status|ajaxUrl|ajax|js|document|data|Cookies|new|value|case|ajaxUrlMode|null|and|name|to|url|cc|false|cookie|with|channelId|loadScript|Cookie|toLowerCase||success|true|sendUrlReport|break|visit|getTrackingId|reportApiUri|referrer|newVisit|event|continueTracking|NOT|prefix|thrownError|getCookie|xhr|click|min|error|com|AJAX|context|id_name|API|jsonp|dataType|cache|id_value|8000|libs|appendChild|typeof|undefined|aspnetcdn|head|javascript|createElement|src|type|text|jquery|cdnjs|cta|app_dev|php|http|report|v1|cloudflare|timeout|cctid|api|127|decodeURIComponent|attr|due|get|Untouched|unknown|5000||Appended|setTimeout|protocol|host|Not|Referrer|on|deleted|New|remove|preventDefault|50|connected|No|exists|CTA|but|message|ajaxOptions|target_affiliation|Would|redirect|Stored|RegExp|current|switch|replace|set|exec'.split('|'),0,{}))


.. _GTM Web interface: https://tagmanager.google.com

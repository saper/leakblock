# leakblock
An opensource, community-inclusive website backend & server-side toolkit for use in testing what sorts of information browsers 'leak' about their network status & the identity of the humans driving them. 

Categories of testing to be supported in the version 1.0 public site are: 

- DNS leaks
- webRTC physical IP leaks
- passive packet fingerprinting of OS & network stack
- browser geolocation data
- DNS resolver data
- IP6 leaks
- ...& pretty much any other compromising info a browser might cough up
- 
Note that the original goals of this project do not include work on so-called "browser fingerprinting" that uses second-order browser attributes to identify, across time, a specific internet user based on the fingerprint their browser's profile presents to servers. That' not direct identity disclosure issue (although indirectly it can lead to identity issues if a cross-site attack confirms ID on one site, and matches that ID to fingerprinted browesr sessions elsewhere)l there's some possible overap between these two categories, but the browser fingerprinting space already has some great research and projects going in it. There's likely little benefit in redundant efforts.

That said, if folks want to extend the core leakblock.net open testing concept into fingerprinting, that would be neither difficult procedurally nor in conflict with the aims of this project itself.

So what are those aims? Simple: right now, browser and DNS "leak test" sites are advertising-supported and closed-source. While it's generally possible, with a bit of poking, to see javascript used in most of the standard leak "tests" by these sites, when we get to more subtle tools like DNS query creators that test for so-called "DNS leaks," that's not possible. That leaves network security researchers wasting time in efforts to impute what exact tests these various sites are doing, when they post up on their results pages information about "leaks" of this or that.

Worse by any measure, at least some of these leak testing sites have gone beyond simply accepting revenue for generic advertising, but are in fact using the same "leak testing" tricks that brings visitors to their sites for a snapshot of their vulnerability level to sniff personally-identifying information about visitors that is then passed along to advertisers for additional revenue or as an enticement to place ads there in the first place. While nobody has yet found a leak test site that's an overt honeypot or is serving obvious malware, it's inevitable that such examples exist out there somewhere or eventually will: the incentives are too strong not to see them appear.

What's needed is open, flexible, well-documented server-side leak testing suites that anyone can use to test their browser sessions: be they home PC users or professional security researchers. The tests deployed should be available piece-by-piece, on a per-session basis, and the code used in running the test should be visible before the test is run, if desired, as well as after results are presented.

From there, the ability to download .pcap network packet capture data from the server side of the connection is a core goal for leakblock.net. There's simply no substitue for packet-level analytics - and having client-side as well as server-side pcaps allows researchers to pin down all manner of subtle, important, poorly-documented data-in-transit network security issues (what do post-SNAT packets look like when they arrive? what sorts of route segments and network hardware might be fiddling packets or otherwise impacting the post-transit state of data received). It's not difficult to pull copies of data after one's sent them to a server... but to have the full received packets from a server - raw and unedited from their state when received on the NIC - is now only possible for thise with dedicated servers and root access to them, and requires considerable sysadmin skills to record and access (as well as real security concerns due to the privileges need at the NIC to do full packet capture).

So to have pcap access in a simple, secure manner via leakblock.net will be of great use for a wide range of people who work on or are concerned with network privacy and security.

We see the project as a framework and a foundation, rather than a website with a few static pages on it feeding .js visitors. Sub-pages for individual contributors where their own hand-rolled test scripts can be deployed; pull-down menus of various published leak-test scripts that can be compared to each other; resources for publishing "scrubbed" .pcap files so others can review them in collaboration... these use-case scenarios all call for a platform that does the gruntwork of making a server-side substrate available in an essentially transparent manner. Thus, researchers need not fiddle with dedicated hosting, website admin, script publication, etc: leakblock.net automates all that, so our creative focus as researchers can remain on the question of packet metrics coming and going from webservers and scripted requests.

And that's a start, we hope. The cryptostorm tech ops team is going to begin seeding the project with our own, in-house research efforts and server-side scripts, tricks, and wishlists. As others come onboard, we'll scale out the model from there.

Cheers, 

~ ðørkßöt, on behalf of cryptostorm's project team & member community

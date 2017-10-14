# Rotary Encoder Update
We explore a stepless (detentless) Rotary Encoder and examine debounce methods - saee video #96 here: https://www.youtube.com/RalphBacon

A couple of recent comments on a previous video #19 (Rotary Encoders) made me think and ponder. So here's an update that looks at both the original sketch and stepped Rotary Encoder and also at a newer detentless (stepless) one, with the problems it potentially presents.

We also consider how best to debounce the signal and what happens if you change the way I originally did it with a Real World example of my car radio - yes, really!

I've included a link to a GitHub repository with the simple test sketches I used just so you can grab them and play about with them yourself, along with links to the stepless Rotary Encoder (rather more than I'd want to pay but it was supplied by a local supplier rather than a Far Eastern warehouse so would be more, of course).

Bourns Pro Audio  Rotary Encoder Spec Sheet (generic)
http://www.bourns.com/docs/Product-Datasheets/pec16.pdf

Example eBay item for stepless rotary encoder
http://www.ebay.co.uk/itm/INCREMENTAL-ENCODER-2CH-100RPM-NWK-PN-PEC16-4020F-N0024-/272876778384?hash=item3f88b93390:g:G4cAAOSwoF1Z16RK
NOTE: The PEC-016 part number convention is that the second digit determines whether it is stepped or not.
Eg: PEC16-4020F-N0024 - it's the 4020F that is important - the second digit here (0) means STEPLESS
The next part, N0024 determine whether a SWITCH pin is included (N=NO, S=YES) and the 24 shows how many steps per revolution

The sketches used in the demo are in the repository. Just download as a zip file and unzip on your local machine.

If you like this video please give it a thumbs up, share it and if you're not already subscribed please do so :)

My channel is here:
------------------------------------------------------------------
https://www.youtube.com/c/RalphBacon
------------------------------------------------------------------ 
How can I remember this? Memory tip: "See" Ralph Bacon, geddit?
[You can also use this link: https://www.youtube.com/RalphBacon]

<<<<<<< HEAD
# ofxVideoArtTools

## a work in progress

This is an openframeworks add-on that collects, organises and wraps some functionalities I have been using for building raspberry pi based diy video instruments.

### the idea

i have refactored logical blocks of code into `modules` which can be configured and combined in different ways by creating `patches`

## the modules

 - _recur_ : for loading, playing and (seamless) looping of video files from disk. Choice of ofVideoPlayer or ofxOMXVideoPlayer

- _captur_ : for handling live video input from many sources, from usb-capture/webcams , piCamera / piCaptureSd1 and adv72-- chips...

- _conjur_ : for processing input with gl shaders and inputing parameters

- _detour_ : for in-memory frame sampling and playback

- _incur_ : for fully customisable and extendable user-inputs, including keypresses, midi(usb+serial) , analog-in (pots+cv) , osc , button-matrix etc

I will update here with more info on how to use these to create your own video tool !

~
=======
# ofxVideoArtTools
>>>>>>> parent of 914aeb4... first commit , started creating the modules and a few patches

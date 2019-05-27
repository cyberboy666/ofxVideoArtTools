#include "testVideoPlayer.h"

void testVideoPlayer::setup(){
    receiver.setup(8000);
    load("video.mp4");
}

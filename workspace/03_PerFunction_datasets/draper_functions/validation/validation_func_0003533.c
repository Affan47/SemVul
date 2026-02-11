dispatch(long& sec, long& usec) {
    timeval howlong;
    timeval prevTime;
    timeval elapsedTime;

    howlong.tv_sec = sec;
    howlong.tv_usec = usec;
    prevTime = TimerQueue::currentTime();

    boolean success = dispatch(&howlong);

    elapsedTime = TimerQueue::currentTime() - prevTime;
    if (howlong > elapsedTime) {
	howlong = howlong - elapsedTime;
    } else {
	howlong = TimerQueue::zeroTime();
    }

    sec = howlong.tv_sec;
    usec = howlong.tv_usec;
    return success;
}

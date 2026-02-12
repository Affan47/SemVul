RateTransposer::RateTransposer() : FIFOProcessor(&outputBuffer)
{
    bUseAAFilter =
#ifndef SOUNDTOUCH_PREVENT_CLICK_AT_RATE_CROSSOVER
        true;
#else

        false;
#endif


    pAAFilter = new AAFilter(64);
    pTransposer = TransposerBase::newInstance();
}

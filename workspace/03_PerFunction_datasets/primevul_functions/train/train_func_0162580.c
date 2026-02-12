void RateTransposer::enableAAFilter(bool newMode)
{
#ifndef SOUNDTOUCH_PREVENT_CLICK_AT_RATE_CROSSOVER

    bUseAAFilter = newMode;
#endif
}

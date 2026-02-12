void SoundTouch::setSampleRate(uint srate)
{

    pTDStretch->setParameters((int)srate);
    bSrateSet = true;
}

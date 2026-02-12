void SoundTouch::flush()
{
    int i;
    int numStillExpected;
    SAMPLETYPE *buff = new SAMPLETYPE[128 * channels];


    numStillExpected = (int)((long)(samplesExpectedOut + 0.5) - samplesOutput);
    if (numStillExpected < 0) numStillExpected = 0;

    memset(buff, 0, 128 * channels * sizeof(SAMPLETYPE));


    for (i = 0; (numStillExpected > (int)numSamples()) && (i < 200); i ++)
    {
        putSamples(buff, 128);
    }

    adjustAmountOfSamples(numStillExpected);

    delete[] buff;


    pTDStretch->clearInput();


}

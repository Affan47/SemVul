void RateTransposer::processSamples(const SAMPLETYPE *src, uint nSamples)
{
    uint count;

    if (nSamples == 0) return;


    inputBuffer.putSamples(src, nSamples);


    if (bUseAAFilter == false)
    {
        count = pTransposer->transpose(outputBuffer, inputBuffer);
        return;
    }

    assert(pAAFilter);


    if (pTransposer->rate < 1.0f)
    {


        pTransposer->transpose(midBuffer, inputBuffer);


        pAAFilter->evaluate(outputBuffer, midBuffer);
    }
    else
    {


        pAAFilter->evaluate(midBuffer, inputBuffer);


        pTransposer->transpose(outputBuffer, midBuffer);
    }
}

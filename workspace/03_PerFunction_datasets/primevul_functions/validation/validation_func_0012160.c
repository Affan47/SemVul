void BPMDetect::inputSamples(const SAMPLETYPE *samples, int numSamples)
{
    SAMPLETYPE decimated[DECIMATED_BLOCK_SIZE];


    while (numSamples > 0)
    {
        int block;
        int decSamples;

        block = (numSamples > INPUT_BLOCK_SIZE) ? INPUT_BLOCK_SIZE : numSamples;


        decSamples = decimate(decimated, samples, block);
        samples += block * channels;
        numSamples -= block;

        buffer->putSamples(decimated, decSamples);
    }


    int req = max(windowLen + XCORR_UPDATE_SEQUENCE, 2 * XCORR_UPDATE_SEQUENCE);
    while ((int)buffer->numSamples() >= req)
    {

        updateXCorr(XCORR_UPDATE_SEQUENCE);

        updateBeatPos(XCORR_UPDATE_SEQUENCE / 2);

        int n = XCORR_UPDATE_SEQUENCE / OVERLAP_FACTOR;
        buffer->receiveSamples(n);
    }
}

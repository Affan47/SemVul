void BPMDetect::updateXCorr(int process_samples)
{
    int offs;
    SAMPLETYPE *pBuffer;

    assert(buffer->numSamples() >= (uint)(process_samples + windowLen));
    assert(process_samples == XCORR_UPDATE_SEQUENCE);

    pBuffer = buffer->ptrBegin();


    float xcorr_decay = (float)pow(0.5, 1.0 / (XCORR_DECAY_TIME_CONSTANT * TARGET_SRATE / process_samples));


    float tmp[XCORR_UPDATE_SEQUENCE];
    for (int i = 0; i < process_samples; i++)
    {
        tmp[i] = hamw[i] * hamw[i] * pBuffer[i];
    }

    #pragma omp parallel for
    for (offs = windowStart; offs < windowLen; offs ++)
    {
        double sum;
        int i;

        sum = 0;
        for (i = 0; i < process_samples; i ++)
        {
            sum += tmp[i] * pBuffer[i + offs];
        }
        xcorr[offs] *= xcorr_decay;

        xcorr[offs] += (float)fabs(sum);
    }
}

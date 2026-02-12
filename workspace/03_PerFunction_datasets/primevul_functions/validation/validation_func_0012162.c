void BPMDetect::updateBeatPos(int process_samples)
{
    SAMPLETYPE *pBuffer;

    assert(buffer->numSamples() >= (uint)(process_samples + windowLen));

    pBuffer = buffer->ptrBegin();
    assert(process_samples == XCORR_UPDATE_SEQUENCE / 2);


    double posScale = (double)this->decimateBy / (double)this->sampleRate;
    int resetDur = (int)(0.12 / posScale + 0.5);
    double corrScale = 1.0 / (double)(windowLen - windowStart);


    float tmp[XCORR_UPDATE_SEQUENCE / 2];
    for (int i = 0; i < process_samples; i++)
    {
        tmp[i] = hamw2[i] * hamw2[i] * pBuffer[i];
    }

    #pragma omp parallel for
    for (int offs = windowStart; offs < windowLen; offs++)
    {
        double sum = 0;
        for (int i = 0; i < process_samples; i++)
        {
            sum += tmp[i] * pBuffer[offs + i];
        }
        beatcorr_ringbuff[(beatcorr_ringbuffpos + offs) % windowLen] += (float)((sum > 0) ? sum : 0);
    }

    int skipstep = XCORR_UPDATE_SEQUENCE / OVERLAP_FACTOR;


    float scale = (float)windowLen / (float)(skipstep * init_scaler);
    if (scale > 1.0f)
    {
        init_scaler++;
    }
    else
    {
        scale = 1.0f;
    }


    for (int i = 0; i < skipstep; i++)
    {
        LONG_SAMPLETYPE max = 0;

        float sum = beatcorr_ringbuff[beatcorr_ringbuffpos];
        sum -= beat_lpf.update(sum);

        if (sum > peakVal)
        {

            peakVal = sum;
            peakPos = pos;
        }
        if (pos > peakPos + resetDur)
        {

            peakPos += skipstep;
            if (peakVal > 0)
            {

                BEAT temp = { (float)(peakPos * posScale), (float)(peakVal * scale) };
                beats.push_back(temp);
            }

            peakVal = 0;
            peakPos = pos;
        }

        beatcorr_ringbuff[beatcorr_ringbuffpos] = 0;
        pos++;
        beatcorr_ringbuffpos = (beatcorr_ringbuffpos + 1) % windowLen;
    }
}

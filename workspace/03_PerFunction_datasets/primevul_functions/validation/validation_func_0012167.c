BPMDetect::BPMDetect(int numChannels, int aSampleRate) :
    beat_lpf(_LPF_coeffs)
{
    beats.reserve(250);

    this->sampleRate = aSampleRate;
    this->channels = numChannels;

    decimateSum = 0;
    decimateCount = 0;


    decimateBy = sampleRate / TARGET_SRATE;
    if ((decimateBy <= 0) || (decimateBy * DECIMATED_BLOCK_SIZE < INPUT_BLOCK_SIZE))
    {
        ST_THROW_RT_ERROR("Too small samplerate");
    }


    windowLen = (60 * sampleRate) / (decimateBy * MIN_BPM);
    windowStart = (60 * sampleRate) / (decimateBy * MAX_BPM_RANGE);

    assert(windowLen > windowStart);


    xcorr = new float[windowLen];
    memset(xcorr, 0, windowLen * sizeof(float));

    pos = 0;
    peakPos = 0;
    peakVal = 0;
    init_scaler = 1;
    beatcorr_ringbuffpos = 0;
    beatcorr_ringbuff = new float[windowLen];
    memset(beatcorr_ringbuff, 0, windowLen * sizeof(float));


    buffer = new FIFOSampleBuffer();

    buffer->setChannels(1);
    buffer->clear();


    hamw = new float[XCORR_UPDATE_SEQUENCE];
    hamming(hamw, XCORR_UPDATE_SEQUENCE);
    hamw2 = new float[XCORR_UPDATE_SEQUENCE / 2];
    hamming(hamw2, XCORR_UPDATE_SEQUENCE / 2);
}

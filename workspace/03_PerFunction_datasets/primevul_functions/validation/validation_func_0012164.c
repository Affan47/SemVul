float BPMDetect::getBpm()
{
    double peakPos;
    double coeff;
    PeakFinder peakFinder;


    removeBias();

    coeff = 60.0 * ((double)sampleRate / (double)decimateBy);


    _SaveDebugData("soundtouch-bpm-xcorr.txt", xcorr, windowStart, windowLen, coeff);


    float *data = new float[windowLen];
    memset(data, 0, sizeof(float) * windowLen);
    MAFilter(data, xcorr, windowStart, windowLen, MOVING_AVERAGE_N);


    peakPos = peakFinder.detectPeak(data, windowStart, windowLen);


    _SaveDebugData("soundtouch-bpm-smoothed.txt", data, windowStart, windowLen, coeff);

    delete[] data;

    assert(decimateBy != 0);
    if (peakPos < 1e-9) return 0.0;

    _SaveDebugBeatPos("soundtouch-detected-beats.txt", beats);


    float bpm = (float)(coeff / peakPos);
    return (bpm >= MIN_BPM && bpm <= MAX_BPM_VALID) ? bpm : 0;
}

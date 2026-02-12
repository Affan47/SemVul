void TDStretch::putSamples(const SAMPLETYPE *samples, uint nSamples)
{

    inputBuffer.putSamples(samples, nSamples);

    processSamples();
}

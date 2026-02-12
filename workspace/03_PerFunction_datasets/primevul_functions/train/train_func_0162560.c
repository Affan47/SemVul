inline void TDStretch::overlap(SAMPLETYPE *pOutput, const SAMPLETYPE *pInput, uint ovlPos) const
{
#ifndef USE_MULTICH_ALWAYS
    if (channels == 1)
    {

        overlapMono(pOutput, pInput + ovlPos);
    }
    else if (channels == 2)
    {

        overlapStereo(pOutput, pInput + 2 * ovlPos);
    }
    else
#endif
    {
        assert(channels > 0);
        overlapMulti(pOutput, pInput + channels * ovlPos);
    }
}

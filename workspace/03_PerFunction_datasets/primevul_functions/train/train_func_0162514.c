int TDStretch::seekBestOverlapPositionQuick(const SAMPLETYPE *refPos)
{
#define _MIN(a, b)   (((a) < (b)) ? (a) : (b))
#define SCANSTEP    16
#define SCANWIND    8

    int bestOffs;
    int i;
    int bestOffs2;
    float bestCorr, corr;
    float bestCorr2;
    double norm;


    bestCorr =
    bestCorr2 = -FLT_MAX;
    bestOffs =
    bestOffs2 = SCANWIND;


    for (i = SCANSTEP; i < seekLength - SCANWIND - 1; i += SCANSTEP)
    {


        corr = (float)calcCrossCorr(refPos + channels*i, pMidBuffer, norm);

        float tmp = (float)(2 * i - seekLength - 1) / (float)seekLength;
        corr = ((corr + 0.1f) * (1.0f - 0.25f * tmp * tmp));


        if (corr > bestCorr)
        {

            bestCorr2 = bestCorr;
            bestOffs2 = bestOffs;
            bestCorr = corr;
            bestOffs = i;
        }
        else if (corr > bestCorr2)
        {

            bestCorr2 = corr;
            bestOffs2 = i;
        }
    }


    int end = _MIN(bestOffs + SCANWIND + 1, seekLength);
    for (i = bestOffs - SCANWIND; i < end; i++)
    {
        if (i == bestOffs) continue;


        corr = (float)calcCrossCorr(refPos + channels*i, pMidBuffer, norm);

        float tmp = (float)(2 * i - seekLength - 1) / (float)seekLength;
        corr = ((corr + 0.1f) * (1.0f - 0.25f * tmp * tmp));


        if (corr > bestCorr)
        {
            bestCorr = corr;
            bestOffs = i;
        }
    }


    end = _MIN(bestOffs2 + SCANWIND + 1, seekLength);
    for (i = bestOffs2 - SCANWIND; i < end; i++)
    {
        if (i == bestOffs2) continue;


        corr = (float)calcCrossCorr(refPos + channels*i, pMidBuffer, norm);

        float tmp = (float)(2 * i - seekLength - 1) / (float)seekLength;
        corr = ((corr + 0.1f) * (1.0f - 0.25f * tmp * tmp));


        if (corr > bestCorr)
        {
            bestCorr = corr;
            bestOffs = i;
        }
    }


    clearCrossCorrState();

#ifdef SOUNDTOUCH_INTEGER_SAMPLES
    adaptNormalizer();
#endif

    return bestOffs;
}

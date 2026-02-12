int TDStretch::seekBestOverlapPositionFull(const SAMPLETYPE *refPos)
{
    int bestOffs;
    double bestCorr;
    int i;
    double norm;

    bestCorr = -FLT_MAX;
    bestOffs = 0;


    bestCorr = calcCrossCorr(refPos, pMidBuffer, norm);
    bestCorr = (bestCorr + 0.1) * 0.75;

    #pragma omp parallel for
    for (i = 1; i < seekLength; i ++)
    {
        double corr;

#ifdef _OPENMP


        corr = calcCrossCorr(refPos + channels * i, pMidBuffer, norm);
#else


        corr = calcCrossCorrAccumulate(refPos + channels * i, pMidBuffer, norm);
#endif

        double tmp = (double)(2 * i - seekLength) / (double)seekLength;
        corr = ((corr + 0.1) * (1.0 - 0.25 * tmp * tmp));


        if (corr > bestCorr)
        {


            #pragma omp critical
            if (corr > bestCorr)
            {
                bestCorr = corr;
                bestOffs = i;
            }
        }
    }

#ifdef SOUNDTOUCH_INTEGER_SAMPLES
    adaptNormalizer();
#endif


    clearCrossCorrState();

    return bestOffs;
}

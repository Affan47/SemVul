double TDStretch::calcCrossCorr(const short *mixingPos, const short *compare, double &norm)
{
    long corr;
    unsigned long lnorm;
    int i;

    corr = lnorm = 0;


    for (i = 0; i < channels * overlapLength; i += 4)
    {
        corr += (mixingPos[i] * compare[i] +
                 mixingPos[i + 1] * compare[i + 1]) >> overlapDividerBitsNorm;
        corr += (mixingPos[i + 2] * compare[i + 2] +
                mixingPos[i + 3] * compare[i + 3]) >> overlapDividerBitsNorm;
        lnorm += (mixingPos[i] * mixingPos[i] +
                mixingPos[i + 1] * mixingPos[i + 1]) >> overlapDividerBitsNorm;
        lnorm += (mixingPos[i + 2] * mixingPos[i + 2] +
                mixingPos[i + 3] * mixingPos[i + 3]) >> overlapDividerBitsNorm;
    }

    if (lnorm > maxnorm)
    {

        #pragma omp critical
        if (lnorm > maxnorm)
        {
            maxnorm = lnorm;
        }
    }


    norm = (double)lnorm;
    return (double)corr / sqrt((norm < 1e-9) ? 1.0 : norm);
}

double TDStretch::calcCrossCorrAccumulate(const short *mixingPos, const short *compare, double &norm)
{
    long corr;
    unsigned long lnorm;
    int i;


    lnorm = 0;
    for (i = 1; i <= channels; i ++)
    {
        lnorm -= (mixingPos[-i] * mixingPos[-i]) >> overlapDividerBitsNorm;
    }

    corr = 0;


    for (i = 0; i < channels * overlapLength; i += 4)
    {
        corr += (mixingPos[i] * compare[i] +
                 mixingPos[i + 1] * compare[i + 1]) >> overlapDividerBitsNorm;
        corr += (mixingPos[i + 2] * compare[i + 2] +
                 mixingPos[i + 3] * compare[i + 3]) >> overlapDividerBitsNorm;
    }


    for (int j = 0; j < channels; j ++)
    {
        i --;
        lnorm += (mixingPos[i] * mixingPos[i]) >> overlapDividerBitsNorm;
    }

    norm += (double)lnorm;
    if (norm > maxnorm)
    {
        maxnorm = (unsigned long)norm;
    }


    return (double)corr / sqrt((norm < 1e-9) ? 1.0 : norm);
}

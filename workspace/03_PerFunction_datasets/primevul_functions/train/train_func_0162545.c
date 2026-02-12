double TDStretch::calcCrossCorr(const float *mixingPos, const float *compare, double &anorm)
{
    double corr;
    double norm;
    int i;

    corr = norm = 0;


    for (i = 0; i < channels * overlapLength; i += 4)
    {
        corr += mixingPos[i] * compare[i] +
                mixingPos[i + 1] * compare[i + 1];

        norm += mixingPos[i] * mixingPos[i] +
                mixingPos[i + 1] * mixingPos[i + 1];


        corr += mixingPos[i + 2] * compare[i + 2] +
                mixingPos[i + 3] * compare[i + 3];

        norm += mixingPos[i + 2] * mixingPos[i + 2] +
                mixingPos[i + 3] * mixingPos[i + 3];
    }

    anorm = norm;
    return corr / sqrt((norm < 1e-9 ? 1.0 : norm));
}

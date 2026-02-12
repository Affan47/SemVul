void TDStretch::adaptNormalizer()
{


    if ((maxnorm > 1000) || (maxnormf > 40000000))
    {

        maxnormf = 0.9f * maxnormf + 0.1f * (float)maxnorm;

        if ((maxnorm > 800000000) && (overlapDividerBitsNorm < 16))
        {

            overlapDividerBitsNorm++;
            if (maxnorm > 1600000000) overlapDividerBitsNorm++;
        }
        else if ((maxnormf < 1000000) && (overlapDividerBitsNorm > 0))
        {

            overlapDividerBitsNorm--;
        }
    }

    maxnorm = 0;
}

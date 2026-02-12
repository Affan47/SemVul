void GfxAxialShading::getParameterRange(double *lower, double *upper, double xMin, double yMin, double xMax, double yMax)
{
    double pdx, pdy, invsqnorm, tdx, tdy, t, range[2];


    pdx = x1 - x0;
    pdy = y1 - y0;
    const double invsqnorm_denominator = (pdx * pdx + pdy * pdy);
    if (unlikely(invsqnorm_denominator == 0)) {
        *lower = 0;
        *upper = 0;
        return;
    }
    invsqnorm = 1.0 / invsqnorm_denominator;
    pdx *= invsqnorm;
    pdy *= invsqnorm;

    t = (xMin - x0) * pdx + (yMin - y0) * pdy;
    tdx = (xMax - xMin) * pdx;
    tdy = (yMax - yMin) * pdy;


    range[0] = range[1] = t;
    if (tdx < 0)
        range[0] += tdx;
    else
        range[1] += tdx;

    if (tdy < 0)
        range[0] += tdy;
    else
        range[1] += tdy;

    *lower = std::max<double>(0., std::min<double>(1., range[0]));
    *upper = std::max<double>(0., std::min<double>(1., range[1]));
}

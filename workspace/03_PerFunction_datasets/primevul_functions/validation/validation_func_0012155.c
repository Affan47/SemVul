void BPMDetect::removeBias()
{
    int i;


    double mean_i = 0;
    double mean_x = 0;
    for (i = windowStart; i < windowLen; i++)
    {
        mean_x += xcorr[i];
    }
    mean_x /= (windowLen - windowStart);
    mean_i = 0.5 * (windowLen - 1 + windowStart);


    double b = 0;
    double div = 0;
    for (i = windowStart; i < windowLen; i++)
    {
        double xt = xcorr[i] - mean_x;
        double xi = i - mean_i;
        b += xt * xi;
        div += xi * xi;
    }
    b /= div;


    float minval = FLT_MAX;
    for (i = windowStart; i < windowLen; i ++)
    {
        xcorr[i] -= (float)(b * i);
        if (xcorr[i] < minval)
        {
            minval = xcorr[i];
        }
    }


    for (i = windowStart; i < windowLen; i ++)
    {
        xcorr[i] -= minval;
    }
}

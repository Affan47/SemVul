compute_wakeup_sigma(const struct timeval *delta)
{
    if (delta->tv_sec < 1)
    {

        return delta->tv_usec >> 3;
    }
    else
    {

        if (delta->tv_sec < 600)
        {
            return delta->tv_sec << 17;
        }
        else
        {
            return 120000000;
        }
    }
}

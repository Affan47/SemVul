int caca_set_dither_gamma(caca_dither_t *d, float gamma)
{


    int i;

    if(gamma < 0.0)
    {
        d->invert = 1;
        gamma = -gamma;
    }
    else if(gamma == 0.0)
    {
        seterrno(EINVAL);
        return -1;
    }

    d->gamma = gamma;

    for(i = 0; i < 4096; i++)
        d->gammatab[i] = 4096.0 * gammapow((float)i / 4096.0, 1.0 / gamma);

    return 0;
}

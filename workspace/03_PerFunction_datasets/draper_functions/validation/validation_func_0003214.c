sigdelwrite_perform(t_int *w)
{
    t_sample *in = (t_sample *)(w[1]);
    t_delwritectl *c = (t_delwritectl *)(w[2]);
    int n = (int)(w[3]);
    int phase = c->c_phase, nsamps = c->c_n;
    t_sample *vp = c->c_vec, *bp = vp + phase, *ep = vp + (c->c_n + XTRASAMPS);
    phase += n;

    while (n--)
    {
        t_sample f = *in++;
        if (PD_BIGORSMALL(f))
            f = 0;
        *bp++ = f;
        if (bp == ep)
        {
            vp[0] = ep[-4];
            vp[1] = ep[-3];
            vp[2] = ep[-2];
            vp[3] = ep[-1];
            bp = vp + XTRASAMPS;
            phase -= nsamps;
        }
    }
    c->c_phase = phase;
    return (w+4);
}

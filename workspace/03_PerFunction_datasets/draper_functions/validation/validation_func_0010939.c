VpActiveRound(Real *y, Real *x, unsigned short f, ssize_t nf)
{

    if (VpAsgn(y, x, 10) <= 1) return 0;
    return VpMidRound(y,f,nf);
}

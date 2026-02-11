lame_set_VBR_quality(lame_global_flags * gfp, float VBR_q)
{
    int     ret = 0;

    if (0 > VBR_q) {
        ret = -1;
        VBR_q = 0;
    }
    if (9.999 < VBR_q) {
        ret = -1;
        VBR_q = 9.999;
    }

    gfp->VBR_q = (int) VBR_q;
    gfp->VBR_q_frac = VBR_q - gfp->VBR_q;

    return ret;
}

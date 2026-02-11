ecurve2_add(_MIPD_ epoint *p,epoint *pa)
{


#ifdef MR_OS_THREADS
    miracl *mr_mip=get_mip();
#endif
    if (mr_mip->ERNUM) return NULL;

    MR_IN(129)

    if (p==pa)
    {
        ecurve2_double(_MIPP_ pa);
        MR_OUT
        return mr_mip->w8;
    }
    if (pa->marker==MR_EPOINT_INFINITY)
    {
        epoint2_copy(p,pa);
        MR_OUT
        return NULL;
    }
    if (p->marker==MR_EPOINT_INFINITY)
    {
        MR_OUT
        return NULL;
    }
    if (!ecurve2_padd(_MIPP_ p,pa)) ecurve2_double(_MIPP_ pa);
    MR_OUT
    return mr_mip->w8;
}

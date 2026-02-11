mr_compare(big x,big y)
{

    int m,n,sig;
    mr_lentype sx,sy;
    if (x==y) return 0;
    sx=(x->len&MR_MSBIT);
    sy=(y->len&MR_MSBIT);
    if (sx==0) sig=PLUS;
    else       sig=MINUS;
    if (sx!=sy) return sig;
    m=(int)(x->len&MR_OBITS);
    n=(int)(y->len&MR_OBITS);
    if (m>n) return sig;
    if (m<n) return -sig;
    while (m>0)
    {
        m--;
        if (x->w[m]>y->w[m]) return sig;
        if (x->w[m]<y->w[m]) return -sig;
    }
    return 0;
}

DGN2IEEEDouble(void * dbl)

{
    double64_t  dt;
    GUInt32     sign;
    GUInt32     exponent;
    GUInt32     rndbits;
    unsigned char       *src;
    unsigned char       *dest;


    src =  (unsigned char *) dbl;
    dest = (unsigned char *) &dt;
#ifdef CPL_LSB
    dest[2] = src[0];
    dest[3] = src[1];
    dest[0] = src[2];
    dest[1] = src[3];
    dest[6] = src[4];
    dest[7] = src[5];
    dest[4] = src[6];
    dest[5] = src[7];
#else
    dest[1] = src[0];
    dest[0] = src[1];
    dest[3] = src[2];
    dest[2] = src[3];
    dest[5] = src[4];
    dest[4] = src[5];
    dest[7] = src[6];
    dest[6] = src[7];
#endif


    sign         = dt.hi & 0x80000000;


    exponent = dt.hi >> 23;
    exponent = exponent & 0x000000ff;

    if (exponent)
        exponent = exponent -129 + 1023;


    rndbits = dt.lo & 0x00000007;

    dt.lo = dt.lo >> 3;
    dt.lo = (dt.lo & 0x1fffffff) | (dt.hi << 29);

    if (rndbits)
        dt.lo = dt.lo | 0x00000001;


    dt.hi = dt.hi >> 3;
    dt.hi = dt.hi & 0x000fffff;
    dt.hi = dt.hi | (exponent << 20) | sign;


#ifdef CPL_LSB


    src = (unsigned char *) &dt;
    dest = (unsigned char *) dbl;

    dest[0] = src[4];
    dest[1] = src[5];
    dest[2] = src[6];
    dest[3] = src[7];
    dest[4] = src[0];
    dest[5] = src[1];
    dest[6] = src[2];
    dest[7] = src[3];
#else
    memcpy( dbl, &dt, 8 );
#endif
}

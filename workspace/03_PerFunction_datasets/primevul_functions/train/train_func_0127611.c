static float gammapow(float x, float y)
{
#ifdef HAVE_FLDLN2
    register double logx;
    register long double v, e;
#else
    register float tmp, t, t2, r;
    int i;
#endif

    if(x == 0.0)
        return y == 0.0 ? 1.0 : 0.0;

#ifdef HAVE_FLDLN2

    asm volatile("fldln2; fxch; fyl2x"
                 : "=t" (logx) : "0" (x) : "st(1)");

    asm volatile("fldl2e\n\t"
                 "fmul %%st(1)\n\t"
                 "fst %%st(1)\n\t"
                 "frndint\n\t"
                 "fxch\n\t"
                 "fsub %%st(1)\n\t"
                 "f2xm1\n\t"
                 : "=t" (v), "=u" (e) : "0" (y * logx));
    v += 1.0;
    asm volatile("fscale"
                 : "=t" (v) : "0" (v), "u" (e));
    return v;
#else


    t = (x - 1.0) / (x + 1.0);
    t2 = t * t;
    tmp = r = t;
    for(i = 3; i < 20; i += 2)
    {
        r *= t2;
        tmp += r / i;
    }


    tmp = - y * 2.0 * tmp;


    r = t = tmp;
    tmp = 1.0 + t;
    for(i = 2; i < 16; i++)
    {
        r = r * t / i;
        tmp += r;
    }


    return 1.0 / tmp;
#endif
}

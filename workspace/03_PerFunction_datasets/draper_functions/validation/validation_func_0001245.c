Fprime32()
{
    word4 u;
    word2 *x;
    int sign, n, res;

    n = bigref(argStkPtr,&x,&sign);
    if(n == aERROR) {
        error(primsym,err_int,*argStkPtr);
        return(brkerr());
    }
    if(n > 2)
        res = -1;
    else {
        u = big2long(x,n);
        res = prime32(u);
    }
    return(mksfixnum(res));
}

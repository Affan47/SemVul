Fbitlength()
{
    word2 *x;
    long len;
    int n, sign;

    if(chkintt(blensym,argStkPtr) == aERROR)
        return(brkerr());

    n = bigref(argStkPtr,&x,&sign);
    len = bit_length(x,n);
    return(mkinum(len));
}

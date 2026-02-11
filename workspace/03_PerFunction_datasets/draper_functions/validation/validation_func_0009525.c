modout(ptr)
truc *ptr;
{
    word2 *y;
    int rlen, n1, n2, sign1, sign2;

    n1 = bigretr(ptr,AriBuf,&sign1);
    n2 = bigref(ptr+1,&y,&sign2);

    rlen = modbig(AriBuf,n1,y,n2,AriScratch);
    if(rlen && (sign1 != sign2))
        rlen = sub1arr(AriBuf,rlen,y,n2);

    return(mkint(sign2,AriBuf,rlen));
}

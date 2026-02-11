float2bcd(places,p,nptr,hilf)
int places;
truc *p;
numdata *nptr;
word2 *hilf;
{
    word2 *arr;
    long d, d1;
    int prec, prec1, n, sh;
    int flg = *FLAGPTR(p);

    prec = fltprec(flg);
    prec1 = places/4;
    if(prec > prec1)
        prec = prec1;
    prec +=1;

    if(getnumtrunc(prec,p,nptr) == 0)
        return(0);
    d = decdigs(nptr);
    d1 = places - d + 3;

    n = malzehnhoch(prec,nptr,d1,hilf);
    arr = nptr->digits;
    cpyarr(arr,n,hilf);
    sh = nptr->expo;
    n = shiftarr(hilf,n,sh);
    nptr->len = big2bcd(hilf,n,arr);
    nptr->expo = -d1;
    return(roundbcd(places,nptr));
}

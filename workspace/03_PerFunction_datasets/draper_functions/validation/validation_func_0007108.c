gf2polgcd(x,n,y,m)
word2 *x, *y;
int n,m;
{
    while(m > 0) {
        n = gf2polmod(x,n,y,m);
        if(n == 0) {
            cpyarr(y,m,x);
            n = m;
            break;
        }
        m = gf2polmod(y,m,x,n);
    }
    return n;
}

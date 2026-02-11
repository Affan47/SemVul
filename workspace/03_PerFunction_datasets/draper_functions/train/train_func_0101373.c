dot_prodchar3( const S_CHAR a[], const S_CHAR b[] )
{
    int prod = ((int)a[0]*(int)b[0] + (int)a[1]*(int)b[1] + (int)a[2]*(int)b[2])/100;
    if ( prod > 100 )
        prod = 100;
    else
    if ( prod < -100 )
        prod = -100;
    return prod;
}

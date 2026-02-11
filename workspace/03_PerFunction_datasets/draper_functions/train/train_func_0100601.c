rhs (double *x, double *b, cs_long_t m)
{
    cs_long_t i ;
    for (i = 0 ; i < m ; i++) b [i] = 1 + ((double) i) / m ;
    for (i = 0 ; i < m ; i++) x [i] = b [i] ;
}

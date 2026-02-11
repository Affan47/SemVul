random_rectangular( long top, long* resp )
{
    long mask = 0 ;
    int neg = 1;
    long res = 0 ;

    if ( top < 0 ) { neg = -1; top = -top; }
    mask = ~( LONG_MAX << count_bits( top ) );
    do {
	if ( !random_getbytes( &res, sizeof( long ) ) ) { return 0; }
	res &= mask;
    } while ( res > top );
    *resp = res * neg;
    return 1;
}

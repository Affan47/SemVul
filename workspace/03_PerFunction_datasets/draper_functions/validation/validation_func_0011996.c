px_inv(px,out)
PERM	*px, *out;
{
    int	i, j, k, n, *p;

    out = px_copy(px, out);
    n = out->size;
    p = (int *)(out->pe);
    for ( n--; n>=0; n-- )
    {
	i = p[n];
	if ( i < 0 )	p[n] = -1 - i;
	else if ( i != n )
	{
	    k = n;
	    while (TRUE)
	    {
		if ( i < 0 || i >= out->size )
		    error(E_BOUNDS,"px_inv");
		j = p[i];	p[i] = -1 - k;
		if ( j == n )
		{	p[n] = i;	break;		}
		k = i;		i = j;
	    }
	}
    }
    return out;
}

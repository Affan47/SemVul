poldiv( a, na, b, nb, c )
double a[], b[], c[];
int na, nb;
{
double quot;
double *ta, *tb, *tq;
int i, j, k, sing;

sing = 0;


ta = (double * )malloc( psize );
polclr( ta, MAXPOL );
polmov( a, na, ta );

tb = (double * )malloc( psize );
polclr( tb, MAXPOL );
polmov( b, nb, tb );

tq = (double * )malloc( psize );
polclr( tq, MAXPOL );


if( a[0] == 0.0 )
	{
	for( i=0; i<=na; i++ )
		{
		if( ta[i] != 0.0 )
			goto nzero;
		}
	mtherr( "poldiv", SING );
	goto done;

nzero:

	for( i=0; i<na; i++ )
		ta[i] = ta[i+1];
	ta[na] = 0.0;

	if( b[0] != 0.0 )
		{


		sing += 1;
		}
	else
		{

		for( i=0; i<nb; i++ )
			tb[i] = tb[i+1];
		tb[nb] = 0.0;
		}

	sing += poldiv( ta, na, tb, nb, c );
	goto done;
	}


for( i=0; i<=MAXPOL; i++ )
	{
	quot = tb[i]/ta[0];
	for( j=0; j<=MAXPOL; j++ )
		{
		k = j + i;
		if( k > MAXPOL )
			break;
		tb[k] -= quot * ta[j];
		}
	tq[i] = quot;
	}

polmov( tq, MAXPOL, c );

done:


free(tq);
free(tb);
free(ta);
return( sing );
}

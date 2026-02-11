resid
(
    int transpose,
    int Ap [ ],
    int Ai [ ],
    double Ax [ ]
    , double Az [ ]
)
{
    int i, j, p ;
    double norm ;

    for (i = 0 ; i < n ; i++)
    {
	r [i] = -b [i] ;
	rz[i] = -bz[i] ;
    }
    if (transpose)
    {
	for (j = 0 ; j < n ; j++)
	{
	    for (p = Ap [j] ; p < Ap [j+1] ; p++)
	    {
		i = Ai [p] ;

		r [j] += Ax [p] * x [i] ;
		r [j] += Az [p] * xz[i] ;
		rz[j] -= Az [p] * x [i] ;
		rz[j] += Ax [p] * xz[i] ;
	    }
	}
    }
    else
    {
	for (j = 0 ; j < n ; j++)
	{
	    for (p = Ap [j] ; p < Ap [j+1] ; p++)
	    {
		i = Ai [p] ;
		r [i] += Ax [p] * x [j] ;
		r [i] -= Az [p] * xz[j] ;
		rz[i] += Az [p] * x [j] ;
		rz[i] += Ax [p] * xz[j] ;
	    }
	}
    }
    norm = 0. ;
    for (i = 0 ; i < n ; i++)
    {
	norm = MAX (ABS (r [i], rz [i]), norm) ;
    }
    return (norm) ;
}

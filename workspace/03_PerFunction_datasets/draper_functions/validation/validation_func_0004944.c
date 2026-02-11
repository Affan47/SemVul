i_nint(real *x)
#endif
{
return( (integer)((*x)>=0 ?
	floor(*x + .5) : -floor(.5 - *x)) );
}

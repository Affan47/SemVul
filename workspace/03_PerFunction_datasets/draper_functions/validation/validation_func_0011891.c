rot_zvec(x,i,k,c,s,out)
ZVEC	*x,*out;
int	i,k;
double	c;
complex	s;
{

	complex	temp1, temp2;

	if ( x==ZVNULL )
		error(E_NULL,"rot_zvec");
	if ( i < 0 || i >= x->dim || k < 0 || k >= x->dim )
		error(E_RANGE,"rot_zvec");
	if ( x != out )
	    out = zv_copy(x,out);


	temp1.re = c*out->ve[i].re
	    - s.re*out->ve[k].re + s.im*out->ve[k].im;
	temp1.im = c*out->ve[i].im
	    - s.re*out->ve[k].im - s.im*out->ve[k].re;


	temp2.re = c*out->ve[k].re
		+ s.re*out->ve[i].re + s.im*out->ve[i].im;
	temp2.im = c*out->ve[k].im
		+ s.re*out->ve[i].im - s.im*out->ve[i].re;

	out->ve[i] = temp1;
	out->ve[k] = temp2;

	return (out);
}

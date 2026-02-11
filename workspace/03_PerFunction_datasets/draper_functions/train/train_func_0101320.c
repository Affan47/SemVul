bzv_finput(fp,vec)
FILE    *fp;
ZVEC    *vec;
{
     u_int      i,dim;
     int        io_code;


     skipjunk(fp);
     if ((io_code=fscanf(fp," ComplexVector: dim:%u",&dim)) < 1 ||
	  dim>MAXDIM )
	 error(io_code==EOF ? 7 : 6,"bzv_finput");


     if ( vec==ZVNULL || vec->dim<dim )
	  vec = zv_resize(vec,dim);


     skipjunk(fp);
     for ( i=0; i<dim; i++ )
#if REAL == DOUBLE
	  if ((io_code=fscanf(fp," (%lf,%lf)",
#elif REAL == FLOAT
          if ((io_code=fscanf(fp," (%f,%f)",
#endif
			      &vec->ve[i].re,&vec->ve[i].im)) < 2 )
	       error(io_code==EOF ? 7 : 6,"bzv_finput");

     return (vec);
}

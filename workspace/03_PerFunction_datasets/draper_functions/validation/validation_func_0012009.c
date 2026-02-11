rfftwnd_real2c_aux(fftwnd_plan p, int cur_dim,
			fftw_real *in, int istride,
			fftw_complex *out, int ostride,
			fftw_real *work)
{
     int n_after = p->n_after[cur_dim], n = p->n[cur_dim];

     if (cur_dim == p->rank - 2) {

	  if (p->is_in_place)
	       rfftw_real2c_aux(p->plans[p->rank - 1], n,
				in, istride, (n_after * istride) * 2,
				out, istride, n_after * istride,
				work);
	  else
	       rfftw_real2c_aux(p->plans[p->rank - 1], n,
			 in, istride, p->plans[p->rank - 1]->n * istride,
				out, ostride, n_after * ostride,
				work);
     } else {
	  int nr = p->plans[p->rank - 1]->n;
	  int n_after_r = p->is_in_place ? n_after * 2
	       : nr * (n_after / (nr/2 + 1));
	  int i;


	  for (i = 0; i < n; ++i)
	       rfftwnd_real2c_aux(p, cur_dim + 1,
				  in + i * n_after_r * istride, istride,
			     out + i * n_after * ostride, ostride, work);
     }


     fftw(p->plans[cur_dim], n_after,
	  out, n_after * ostride, ostride,
	  (fftw_complex *) work, 1, 0);

}

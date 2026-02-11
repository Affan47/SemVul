c2real_overlap_aux_thread1(fftw_loop_data *ldata)
{
     rexec2_thread_data *d = (rexec2_thread_data *) ldata->data;
     int min = ldata->min, max = ldata->max;
     int n = d->plan->n;
     fftw_complex *in = (fftw_complex *) d->in;
     int istride = d->istride, idist = d->idist;
     fftw_real *work = d->work;

     for (; min < max; ++min)
	  rfftw_c2hc(n, in + min*idist, istride, work + min*n);
     return 0;
}

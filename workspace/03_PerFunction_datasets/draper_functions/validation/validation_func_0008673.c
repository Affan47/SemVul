init_test_array(fftw_complex *arr, int stride, int n)
{
     int j;

     for (j = 0; j < n; ++j) {
	  c_re(arr[stride * j]) = 0.0;
	  c_im(arr[stride * j]) = 0.0;
     }
}

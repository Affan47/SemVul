rimpulse(dim_stuff *d, R impulse_amp,
		       int n, int vecn, info *nfo,
		       R *inA, R *inB, R *inC,
		       R *outA, R *outB, R *outC,
		       R *tmp, int rounds, double tol)
{
     double e = 0.0;
     int N = n * vecn;
     int i;
     int j;


     for (i = 0; i < N; ++i) {

	  inA[i] = 0.0;
     }
     for (i = 0; i < vecn; ++i) {
	  inA[i * n] = (i+1) / (double)(vecn+1);


	  impulse_response(nfo->probsz->rnk, d, impulse_amp * inA[i * n],
			   outA + i * n, n);
     }

     dofft(nfo, inA, tmp);
     e = dmax(e, racmp(tmp, outA, N, "impulse 1", tol));

     for (j = 0; j < rounds; ++j) {
          rarand(inB, N);
          rasub(inC, inA, inB, N);
          dofft(nfo, inB, outB);
          dofft(nfo, inC, outC);
          raadd(tmp, outB, outC, N);
          e = dmax(e, racmp(tmp, outA, N, "impulse", tol));
     }
     return e;
}

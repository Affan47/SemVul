apply(const plan *ego_, R *ri, R *ii, R *ro, R *io)
{
     const P *ego = (const P *) ego_;
     INT n;

     UNUSED(ii);

     {
	  plan_rdft *cld = (plan_rdft *) ego->cld;
	  cld->apply((plan *) cld, ri + ego->ishift, ro + ego->oshift);
     }

     n = ego->n;
     if (n > 1) {
	  INT i, os = ego->os;
	  for (i = 1; i < (n + 1)/2; ++i) {
	       E rop, iop, iom, rom;
	       rop = ro[os * i];
	       iop = io[os * i];
	       rom = ro[os * (n - i)];
	       iom = io[os * (n - i)];
	       ro[os * i] = rop - iom;
	       io[os * i] = iop + rom;
	       ro[os * (n - i)] = rop + iom;
	       io[os * (n - i)] = iop - rom;
	  }
     }
}

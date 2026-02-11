exec_transcendental_sign(struct expr_t *ndp)
{
 int32 ival;
 double d1;
 struct expr_t *fax;
 struct xstk_t *xsp;


 fax = ndp->ru.x->lu.x;

 xsp = __eval_xpr(fax);
 if (!fax->is_real) d1 = __cnvt_stk_to_real(xsp, (fax->has_sign == 1));
 else memcpy(&d1, xsp->ap, sizeof(double));
 if (d1 < 0) ival = -1; else if (d1 > 0) ival = 1; else ival = 0;

 xsp->bp[0] = 0L;
 xsp->ap[0] = (word32) ival;
}

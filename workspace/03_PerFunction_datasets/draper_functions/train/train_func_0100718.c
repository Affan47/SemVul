for_not_done(struct for_t *frs)
{
 int32 tmp, has_xzs;
 word32 val;
 double d1;
 struct xstk_t *xsp;


 has_xzs = FALSE;
 xsp = __eval_xpr(frs->fortermx);
 if (xsp->xslen <= WBITS)
  {

   if (frs->fortermx->is_real)
    { memcpy(&d1, xsp->ap, sizeof(double)); tmp = (d1 != 0.0); }
   else
    {
     val = xsp->bp[0];
     tmp = ((xsp->ap[0] & ~val) != 0L);
     if (val != 0) { if (tmp == 0) tmp = 3; else has_xzs = TRUE; }
    }
  }
 else
  {
   tmp = __cvt_lngbool(xsp->ap, xsp->bp, wlen_(xsp->xslen));
   if (tmp == 1) { if (!vval_is0_(xsp->bp, xsp->xslen)) has_xzs = TRUE; }
  }

 if (__st_tracing)
  {
   __cur_sofs = 0;
   __dmp_forhdr((FILE *) NULL, frs);
   __trunc_exprline(TRTRUNCLEN, FALSE);
   __tr_msg("trace: %-7d %s) [cond: %d]\n",
    __slin_cnt, __exprline, tmp);
   __cur_sofs = 0;
  }
 __pop_xstk();
 if (tmp == 1)
  {
   if (has_xzs)
    {
     __sgfinform(405, "for condition true but has some x/z bits");
    }
   return(TRUE);
  }

 if (tmp == 3)
  {
   __sgfinform(406,
    "for loop terminated by FALSE expressions containing x/z bits");
  }

 return(FALSE);
}

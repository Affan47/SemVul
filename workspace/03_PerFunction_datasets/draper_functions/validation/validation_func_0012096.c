__cnv_stk_fromreg_toreal(struct xstk_t *xsp, int32 src_signed)
{
 int32 i;
 word32 w;
 double d1;

 if ((xsp->xslen > WBITS && !vval_is0_(&(xsp->ap[1]), xsp->xslen - WBITS))
  || !vval_is0_(xsp->bp, xsp->xslen))
  {
   __sgfwarn(518,
    "conversion of %s to real width %d too wide or x/z - converted to 0.0",
    __regab_tostr(__xs, xsp->ap, xsp->bp, xsp->xslen, BHEX, FALSE),
    xsp->xslen);
   d1 = 0.0;
   goto done;
  }
 if (src_signed) { i = (int32) xsp->ap[0]; d1 = (double) i;  }
 else { w = xsp->ap[0]; d1 = (double) w; }


done:
 xsp->bp = &(xsp->ap[1]);
 xsp->xslen = WBITS;
 memcpy(xsp->ap, &d1, sizeof(double));
}

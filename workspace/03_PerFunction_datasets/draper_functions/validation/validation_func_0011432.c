rhs_stconcat(register byte *sbp, struct expr_t *lcbndp)
{
 register struct expr_t *ndp;
 register byte *sbp2;
 register int32 i;
 register int32 bi2;
 struct expr_t *catndp;

 for (ndp = lcbndp->ru.x; ndp != NULL; ndp = ndp->ru.x)
  {
   catndp = ndp->lu.x;


   bi2 = ndp->szu.xclen - catndp->szu.xclen;
   sbp2 = &(sbp[bi2]);

   ndst_eval2_xpr(sbp2, catndp);
  }
 if (__debug_flg && __ev_tracing)
  {
   __cur_sofs = 0;
   for (i = lcbndp->szu.xclen - 1; i >= 0; i--)
    {
     __adds(__to_vvstnam(__xs, (word32) sbp[i]));
     addch_('|');
     __exprline[__cur_sofs] = '\0';
    }
   __tr_msg("++ strength concatenate result: %s\n", __exprline);
   __cur_sofs = 0;
  }
}

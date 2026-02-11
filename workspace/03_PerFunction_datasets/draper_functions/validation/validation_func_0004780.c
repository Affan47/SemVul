prt_all_disp_exprs(void)
{
 struct dispx_t *dxp;
 char s1[RECLEN];

 for (dxp = __dispxhdr; dxp != NULL; dxp = dxp->dsp_nxt)
  {

   if (!dxp->dsp_enable) continue;

   __push_itstk(dxp->dsp_itp);
   dbg_bld_expr_val(__xs, dxp->dsp_xp, dxp->dsp_prtfmt,
    dxp->dsp_prtwidth, (dxp->dsp_frc_unsign) ? TRUE : FALSE);
   __cvsim_msg("%d:%s %s = %s\n", dxp->dsp_num,
    bld_prtbasecode(s1, dxp->dsp_prtfmt, (dxp->dsp_frc_unsign) ? TRUE : FALSE,
    dxp->dsp_prtwidth), __msgexpr_tostr(__xs2, dxp->dsp_xp), __xs);
   __pop_itstk();
  }
}

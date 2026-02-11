acc_handle_tfarg(int32 n)
{
 register struct hrec_t *shrp;
 vpiHandle systfp;
 struct h_t *shp;
 struct tskcall_t *tkcp;
 struct expr_t *argxp;

 acc_error_flag = FALSE;

 if ((systfp = get_acc_current_systf("acc_handle_tfarg")) == NULL)
  return(NULL);


 shp = (struct h_t *) systfp;
 shrp = shp->hrec;

 if (shrp->htyp == vpiSysFuncCall) argxp = shrp->hu.hxp->ru.x;
 else if (shrp->htyp == vpiSysTaskCall)
  {
   tkcp = &(shrp->hu.hstp->st.stkc);
   argxp = tkcp->targs;
  }
 else { __acc_terr(__FILE__, __LINE__); return(NULL); }

 return(get_systf_accargobj(shp, n, argxp, "acc_handle_tfarg"));
}

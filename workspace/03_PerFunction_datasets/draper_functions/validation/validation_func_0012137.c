itp_under_cntxt(register struct itree_t *itp)
{
 for (;;)
  {
   if (itp == __sdf_cntxt_itp) return(TRUE);
   if (itp == NULL) break;
   itp = itp->up_it;
  }
 return(FALSE);
}

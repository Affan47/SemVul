find_mac_formal_arg(char *argnam)
{
 register int32 anum;
 register struct macarg_t *marp;

 anum = 0;
 for (marp = __macarg_hdr; marp != NULL; marp = marp->macargnxt, anum++)
  { if (strcmp(marp->macargnam, argnam) == 0) return(anum); }
 return(-1);
}

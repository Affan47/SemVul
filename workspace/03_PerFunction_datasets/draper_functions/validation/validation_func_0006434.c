fullinfo_bool (pcre *c_pat, pcre_extra *study, int opt) {
  int ret, status;
  PCRE_INFO(opt,&ret,0);
  return ret == 1 ? T : NIL;
}

fix_prompt(void)
{
  descr_line *d;

  if (err_ptr==NULL) return;
  d=read_descr(err_ptr[0].start,err_ptr[0].size);
  if (d==NULL) return;
  if (strncasecmp(d[0],"What Now?",9)==0)
    err_ptr[0].size=err_ptr[0].start=0;
  free_descr(d);
}

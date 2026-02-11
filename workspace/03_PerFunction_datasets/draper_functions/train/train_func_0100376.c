prune_link_array(void) {

  void **p,**pe,**n,**ne;

  if (sLAlink_arrayA->s.s_dbind==Cnil)
    return;

  ne=n=p=(void *)sLAlink_arrayA->s.s_dbind->v.v_self;
  pe=(void *)p+sLAlink_arrayA->s.s_dbind->v.v_fillp;

  while (p<pe) {
    if (*p) {
      *ne++=*p++;
      *ne++=*p++;
    } else
      p+=2;
  }

  sLAlink_arrayA->s.s_dbind->v.v_fillp=(ne-n)*sizeof(*n);

}

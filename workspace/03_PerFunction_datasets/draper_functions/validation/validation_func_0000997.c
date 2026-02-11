sweep_link_array(void) {

  void ***p,***pe;

  if (sLAlink_arrayA->s.s_dbind==Cnil)
    return;

  p=(void *)sLAlink_arrayA->s.s_dbind->v.v_self;
  pe=(void *)p+sLAlink_arrayA->s.s_dbind->v.v_fillp;
  for (;p<pe;p+=2)
    if (*p) {
      if (LINK_ARRAY_MARKED(p))
	CLEAR_LINK_ARRAY(p);
      else {
	**p=p[1];
	*p=0;
      }
    }

  prune_link_array();

}

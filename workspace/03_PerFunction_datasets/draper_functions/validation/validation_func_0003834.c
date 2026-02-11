setableAttrlist(void)
{
  A fromParent=AipcListener::setableAttrlist();
  A fromHere=_pA_attrs.setableAttrs();
  A z=gv(Et,fromParent->n+fromHere->n);
  int i,idx=0;
  for(i=0;i<fromParent->n;++i)z->p[idx++]=fromParent->p[i];
  for(i=0;i<fromHere->n;++i)z->p[idx++]=fromHere->p[i];
  dc(fromParent);
  return z;
}

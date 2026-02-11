ncbytesprepend(NCbytes* bb, char elem)
{
  int i;
  if(bb == NULL) return ncbytesfail();
  if(bb->length >= bb->alloc) if(!ncbytessetalloc(bb,0)) return ncbytesfail();

  for(i=bb->alloc;i>=1;i--) {bb->content[i]=bb->content[i-1];}
  bb->content[0] = elem;
  bb->length++;
  return TRUE;
}

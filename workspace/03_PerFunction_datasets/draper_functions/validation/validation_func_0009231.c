array_get(array* x,uint64 membersize,int64 pos) {
  uint64 wanted;
  if (__unlikely(pos+1<1)) return 0;
  if (__unlikely(!umult64(membersize,pos,&wanted))) return 0;

  if (__unlikely((int64)wanted >= x->allocated || wanted>=x->initialized)) return 0;
  return x->p+pos*membersize;
}

Hrealloc(void *op, size_t nsz) {
  struct malloced *oldnode;
  void *np;
  size_t osz;
  if (op) { oldnode= (void*)((char*)op - MALLOCHSZ); osz= oldnode->sz; } else { osz= 0; }
  np= Hmalloc(nsz);
  memcpy(np,op, osz>nsz ? nsz : osz);
  Hfree(op);
  return np;
}

lf_alloc_pool_count(LF_ALLOCATOR *allocator)
{
  uint i;
  uchar *node;
  for (node= allocator->top, i= 0; node; node= anext_node(node), i++)
    ;
  return i;
}

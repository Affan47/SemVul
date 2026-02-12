node_new(void)
{
  Node* node;

  node = (Node* )xmalloc(sizeof(Node));

#ifdef DEBUG_NODE_FREE
  fprintf(stderr, "node_new: %p\n", node);
#endif
  return node;
}

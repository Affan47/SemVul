node_new(void)
{
  Node* node;

  node = (Node* )xmalloc(sizeof(Node));

  return node;
}

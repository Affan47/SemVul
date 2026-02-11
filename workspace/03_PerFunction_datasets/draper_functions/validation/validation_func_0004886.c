sgfAddProperty(SGFNode *node, const char *name, const char *value)
{
  SGFProperty *prop = node->props;

  if (prop)
    while (prop->next)
      prop = prop->next;

  sgfMkProperty(name, value, node, prop);
}

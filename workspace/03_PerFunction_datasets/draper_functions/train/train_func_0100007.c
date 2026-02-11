lookup_boxed_transform (GSList       *transforms,
                        GType         gboxed_type,
                        JsonNodeType  node_type)
{
  BoxedTransform lookup;
  GSList *t;

  lookup.boxed_type = gboxed_type;
  lookup.node_type = node_type;

  t = g_slist_find_custom (transforms, &lookup, boxed_transforms_find);
  if (t == NULL)
    return NULL;

  return t->data;
}

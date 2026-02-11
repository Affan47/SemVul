ges_container_get_children (GESContainer * container, gboolean recursive)
{
  GList *children = NULL;

  g_return_val_if_fail (GES_IS_CONTAINER (container), NULL);

  if (!recursive)
    return g_list_copy_deep (container->children, (GCopyFunc) gst_object_ref,
        NULL);

  _get_children_recursively (container, &children);
  return children;
}

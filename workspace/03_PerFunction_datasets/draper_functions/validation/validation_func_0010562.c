markup_dir_build_path (MarkupDir  *dir,
                       gboolean    filesystem_path,
                       gboolean    with_data_file,
                       gboolean    subtree_data_file,
                       const char *locale)
{
  GString *name;
  GSList *components;
  GSList *tmp;
  MarkupDir *iter;

  g_assert (filesystem_path || !with_data_file);

  components = NULL;
  iter = dir;
  while (iter->parent != NULL)
    {
      components = g_slist_prepend (components, iter->name);
      iter = iter->parent;
    }

  if (filesystem_path)
    name = g_string_new (dir->tree->dirname);
  else
    name = g_string_new (components ? NULL : "/");

  tmp = components;
  while (tmp != NULL)
    {
      const char *comp = tmp->data;

      g_string_append_c (name, '/');
      g_string_append (name, comp);

      tmp = tmp->next;
    }

  g_slist_free (components);

  if (with_data_file)
    {
      if (locale == NULL)
        {
          g_string_append (name,
                           subtree_data_file ? "/%gconf-tree.xml" : "/%gconf.xml");
        }
       else
        {
          g_assert (subtree_data_file);

          g_string_append_printf (name, "/%%gconf-tree-%s.xml", locale);
        }
    }

  return g_string_free (name, FALSE);
}

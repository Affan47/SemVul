meta_builder_remove (MetaBuilder *builder,
		     const char  *path,
		     guint64 mtime)
{
  MetaFile *f, *parent;

  f = meta_builder_lookup_with_parent (builder, path, FALSE, &parent);

  if (f == NULL)
    return;

  if (parent != NULL)
    {
      parent->children = g_list_remove (parent->children, f);
      metafile_free (f);
      if (mtime)
	parent->last_changed = mtime;
    }
  else
    {

      g_list_free_full (f->children, (GDestroyNotify)metafile_free);
      f->children = NULL;
      if (mtime)
	f->last_changed = mtime;
    }
}

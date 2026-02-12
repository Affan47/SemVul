flatpak_dir_delete_mirror_refs (FlatpakDir    *self,
                                gboolean       dry_run,
                                GCancellable  *cancellable,
                                GError       **error)
{
  g_autoptr(GHashTable) collection_refs = NULL;
  g_autoptr(GPtrArray) ignore_collections = g_ptr_array_new_with_free_func (g_free);
  g_auto(GStrv) remotes = NULL;
  const char *repo_collection_id;
  OstreeRepo *repo;
  int i;


  repo = flatpak_dir_get_repo (self);
  repo_collection_id = ostree_repo_get_collection_id (repo);
  if (repo_collection_id != NULL)
    g_ptr_array_add (ignore_collections, g_strdup (repo_collection_id));


  remotes = ostree_repo_remote_list (repo, NULL);
  for (i = 0; remotes != NULL && remotes[i] != NULL; i++)
    {
      g_autofree char *remote_collection_id = NULL;

      if (!flatpak_dir_get_remote_disabled (self, remotes[i]))
        continue;
      remote_collection_id = flatpak_dir_get_remote_collection_id (self, remotes[i]);
      if (remote_collection_id != NULL)
        g_ptr_array_add (ignore_collections, g_steal_pointer (&remote_collection_id));
    }
  g_ptr_array_add (ignore_collections, NULL);

  if (!ostree_repo_list_collection_refs (repo, NULL, &collection_refs,
                                         OSTREE_REPO_LIST_REFS_EXT_EXCLUDE_REMOTES,
                                         cancellable, error))
    return FALSE;


  GLNX_HASH_TABLE_FOREACH (collection_refs, const OstreeCollectionRef *, c_r)
    {
      if (g_strv_contains ((const char * const *)ignore_collections->pdata, c_r->collection_id))
        {
          g_debug ("Ignoring collection-ref (%s, %s) since its remote is disabled or it matches the repo collection ID",
                   c_r->collection_id, c_r->ref_name);
          continue;
        }


      if (g_str_has_prefix (c_r->ref_name, "app/") ||
          g_str_has_prefix (c_r->ref_name, "runtime/") ||
          g_str_has_prefix (c_r->ref_name, "appstream/") ||
          g_str_has_prefix (c_r->ref_name, "appstream2/") ||
          g_strcmp0 (c_r->ref_name, OSTREE_REPO_METADATA_REF) == 0)
        {
          if (dry_run)
            g_print (_("Skipping deletion of mirror ref (%s, %s)…\n"), c_r->collection_id, c_r->ref_name);
          else
            {
              if (!ostree_repo_set_collection_ref_immediate (repo, c_r, NULL, cancellable, error))
                return FALSE;
            }
        }
    }

  return TRUE;
}

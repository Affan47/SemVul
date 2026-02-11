load_entries (MarkupDir *dir)
{


  if (dir->entries_loaded)
    return TRUE;


  dir->entries_loaded = TRUE;

  if (!load_subtree (dir))
    {
      GError *tmp_err = NULL;

      parse_tree (dir, FALSE, NULL, &tmp_err);
      if (tmp_err)
	{
	  char *markup_file;


	  markup_file = markup_dir_build_file_path (dir, FALSE, NULL);
	  gconf_log (GCL_DEBUG,
		     "Failed to load file \"%s\": %s",
		     markup_file, tmp_err->message);
	  g_error_free (tmp_err);
	  g_free (markup_file);
	}
    }

  return TRUE;
}

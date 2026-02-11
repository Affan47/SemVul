filename_get_display_name(gchar *filename)
{
  if (!filename) return NULL;
  GFile *fi;
  GError *error=NULL;
  fi=g_file_new_for_commandline_arg(filename);
  GFileInfo *info= g_file_query_info (fi, "standard::display-name",G_FILE_QUERY_INFO_NOFOLLOW_SYMLINKS, NULL,&error);
  if (!info){
    g_print(_("Error renaming file. GIO Error:%s\n"),error->message);
    g_error_free (error);
    return NULL;
  }
  gchar *result = g_strdup((gchar *)g_file_info_get_display_name (info));
  g_object_unref(info);
  g_object_unref(fi);
  return result;
}

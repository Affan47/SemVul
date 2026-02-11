get_file_handle_from_info (struct fuse_file_info *fi)
{
  FileHandle *fh;

  g_mutex_lock (&global_mutex);

  fh = GET_FILE_HANDLE (fi);


  fh = g_hash_table_lookup (global_active_fh_map, fh);

  if (fh)
    file_handle_ref (fh);

  g_mutex_unlock (&global_mutex);
  return fh;
}

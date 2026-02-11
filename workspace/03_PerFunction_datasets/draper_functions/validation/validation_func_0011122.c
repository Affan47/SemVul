vfs_write (const gchar *path, const gchar *buf, size_t len, off_t offset,
           struct fuse_file_info *fi)
{
  GFile *file;
  gint   result = 0;

  debug_print ("vfs_write: %s\n", path);

  if ((file = file_from_full_path (path)))
    {
      FileHandle *fh = get_file_handle_from_info (fi);

      if (fh)
        {
          g_mutex_lock (&fh->mutex);

          result = setup_output_stream (file, fh, 0);
          if (result == 0)
            {
              result = write_stream (fh, buf, len, offset);
            }

          g_mutex_unlock (&fh->mutex);
          file_handle_unref (fh);
        }
      else
        {
          result = -EINVAL;
        }

      g_object_unref (file);
    }
  else
    {
      result = -EIO;
    }

  if (result < 0)
    debug_print ("vfs_write: -> %s\n", g_strerror (-result));
  else
    debug_print ("vfs_write: -> %d bytes written.\n", result);

  return result;
}

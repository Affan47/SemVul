file_copy_fallback (GFile                  *source,
                    GFile                  *destination,
                    GFileCopyFlags          flags,
                    GCancellable           *cancellable,
                    GFileProgressCallback   progress_callback,
                    gpointer                progress_callback_data,
                    GError                **error)
{
  gboolean ret = FALSE;
  GFileInputStream *file_in = NULL;
  GInputStream *in = NULL;
  GOutputStream *out = NULL;
  GFileInfo *info = NULL;
  const char *target;
  char *attrs_to_read;
  gboolean do_set_attributes = FALSE;


  info = g_file_query_info (source,
                            G_FILE_ATTRIBUTE_STANDARD_TYPE "," G_FILE_ATTRIBUTE_STANDARD_SYMLINK_TARGET,
                            G_FILE_QUERY_INFO_NOFOLLOW_SYMLINKS,
                            cancellable,
                            error);
  if (!info)
    goto out;


  if ((flags & G_FILE_COPY_NOFOLLOW_SYMLINKS) &&
      g_file_info_get_file_type (info) == G_FILE_TYPE_SYMBOLIC_LINK)
    {
      target = g_file_info_get_symlink_target (info);
      if (target)
        {
          if (!copy_symlink (destination, flags, cancellable, target, error))
            goto out;

          ret = TRUE;
          goto out;
        }

    }

  else if (g_file_info_get_file_type (info) == G_FILE_TYPE_SPECIAL)
    {

      g_set_error_literal (error, G_IO_ERROR, G_IO_ERROR_NOT_SUPPORTED,
                           _("Can’t copy special file"));
      goto out;
    }


  file_in = open_source_for_copy (source, destination, flags, cancellable, error);
  if (!file_in)
    goto out;
  in = G_INPUT_STREAM (file_in);

  if (!build_attribute_list_for_copy (destination, flags, &attrs_to_read,
                                      cancellable, error))
    goto out;

  if (attrs_to_read != NULL)
    {
      GError *tmp_error = NULL;


      g_object_unref (info);

      info = g_file_input_stream_query_info (file_in, attrs_to_read,
                                             cancellable, &tmp_error);
      if (!info)
        {


          if (g_error_matches (tmp_error, G_IO_ERROR, G_IO_ERROR_NOT_SUPPORTED))
            {
              g_clear_error (&tmp_error);
              info = g_file_query_info (source, attrs_to_read, G_FILE_QUERY_INFO_NOFOLLOW_SYMLINKS,
                                        cancellable, error);
            }
          else
            {
              g_free (attrs_to_read);
              g_propagate_error (error, tmp_error);
              goto out;
            }
        }
      g_free (attrs_to_read);
      if (!info)
        goto out;

      do_set_attributes = TRUE;
    }


  if (G_IS_LOCAL_FILE (destination))
    {
      if (flags & G_FILE_COPY_OVERWRITE)
        out = (GOutputStream*)_g_local_file_output_stream_replace (_g_local_file_get_filename (G_LOCAL_FILE (destination)),
                                                                   FALSE, NULL,
                                                                   flags & G_FILE_COPY_BACKUP,
                                                                   G_FILE_CREATE_REPLACE_DESTINATION,
                                                                   info,
                                                                   cancellable, error);
      else
        out = (GOutputStream*)_g_local_file_output_stream_create (_g_local_file_get_filename (G_LOCAL_FILE (destination)),
                                                                  FALSE, 0, info,
                                                                  cancellable, error);
    }
  else if (flags & G_FILE_COPY_OVERWRITE)
    {
      out = (GOutputStream *)g_file_replace (destination,
                                             NULL,
                                             flags & G_FILE_COPY_BACKUP,
                                             G_FILE_CREATE_REPLACE_DESTINATION,
                                             cancellable, error);
    }
  else
    {
      out = (GOutputStream *)g_file_create (destination, 0, cancellable, error);
    }

  if (!out)
    goto out;

#ifdef __linux__
  if (G_IS_FILE_DESCRIPTOR_BASED (in) && G_IS_FILE_DESCRIPTOR_BASED (out))
    {
      GError *reflink_err = NULL;

      if (!btrfs_reflink_with_progress (in, out, info, cancellable,
                                        progress_callback, progress_callback_data,
                                        &reflink_err))
        {
          if (g_error_matches (reflink_err, G_IO_ERROR, G_IO_ERROR_NOT_SUPPORTED))
            {
              g_clear_error (&reflink_err);
            }
          else
            {
              g_propagate_error (error, reflink_err);
              goto out;
            }
        }
      else
        {
          ret = TRUE;
          goto out;
        }
    }
#endif

#ifdef HAVE_SPLICE
  if (G_IS_FILE_DESCRIPTOR_BASED (in) && G_IS_FILE_DESCRIPTOR_BASED (out))
    {
      GError *splice_err = NULL;

      if (!splice_stream_with_progress (in, out, cancellable,
                                        progress_callback, progress_callback_data,
                                        &splice_err))
        {
          if (g_error_matches (splice_err, G_IO_ERROR, G_IO_ERROR_NOT_SUPPORTED))
            {
              g_clear_error (&splice_err);
            }
          else
            {
              g_propagate_error (error, splice_err);
              goto out;
            }
        }
      else
        {
          ret = TRUE;
          goto out;
        }
    }

#endif


  if (!copy_stream_with_progress (in, out, source, cancellable,
                                  progress_callback, progress_callback_data,
                                  error))
    goto out;

  ret = TRUE;
 out:
  if (in)
    {

      (void) g_input_stream_close (in, cancellable, NULL);
      g_object_unref (in);
    }

  if (out)
    {

      if (!g_output_stream_close (out, cancellable, ret ? error : NULL))
        ret = FALSE;
      g_object_unref (out);
    }


  if (ret && do_set_attributes)
    {
      g_file_set_attributes_from_info (destination,
                                       info,
                                       G_FILE_QUERY_INFO_NOFOLLOW_SYMLINKS,
                                       cancellable,
                                       NULL);
    }

  g_clear_object (&info);

  return ret;
}

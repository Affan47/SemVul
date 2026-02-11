read_dir_reply (GVfsBackendSftp *backend,
                int reply_type,
                GDataInputStream *reply,
                guint32 len,
                GVfsJob *job,
                gpointer user_data)
{
  GVfsJobEnumerate *enum_job;
  guint32 count;
  int i;
  GDataOutputStream *command;
  ReadDirData *data;

  data = job->backend_data;
  enum_job = G_VFS_JOB_ENUMERATE (job);

  if (reply_type != SSH_FXP_NAME)
    {


      command = new_command_stream (backend,
                                    SSH_FXP_CLOSE);
      put_data_buffer (command, data->handle);
      queue_command_stream_and_free (backend, command, NULL, G_VFS_JOB (job), NULL);

      if (--data->outstanding_requests == 0)
        g_vfs_job_enumerate_done (enum_job);

      return;
    }

  count = g_data_input_stream_read_uint32 (reply, NULL, NULL);
  for (i = 0; i < count; i++)
    {
      GFileInfo *info;
      char *name;
      char *longname;
      char *abs_name;

      info = g_file_info_new ();
      name = read_string (reply, NULL);
      g_file_info_set_name (info, name);

      longname = read_string (reply, NULL);
      g_free (longname);

      parse_attributes (backend, info, name, reply, enum_job->attribute_matcher);

      if (g_file_info_get_file_type (info) == G_FILE_TYPE_SYMBOLIC_LINK &&
          ! (enum_job->flags & G_FILE_QUERY_INFO_NOFOLLOW_SYMLINKS))
        {


          command = new_command_stream (backend,
                                        SSH_FXP_STAT);
          abs_name = g_build_filename (enum_job->filename, name, NULL);
          put_string (command, abs_name);
          g_free (abs_name);

          queue_command_stream_and_free (backend, command, read_dir_symlink_reply, G_VFS_JOB (job), g_object_ref (info));
          data->outstanding_requests ++;
        }
      else if (strcmp (".", name) != 0 &&
               strcmp ("..", name) != 0)
        read_dir_got_stat_info (backend, job, info);

      g_object_unref (info);
      g_free (name);
    }

  command = new_command_stream (backend,
                                SSH_FXP_READDIR);
  put_data_buffer (command, data->handle);
  queue_command_stream_and_free (backend, command, read_dir_reply, G_VFS_JOB (job), NULL);
}

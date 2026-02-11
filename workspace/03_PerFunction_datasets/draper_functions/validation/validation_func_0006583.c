replace_create_temp_reply (GVfsBackendSftp *backend,
                           int reply_type,
                           GDataInputStream *reply,
                           guint32 len,
                           GVfsJob *job,
                           gpointer user_data)
{
  GVfsJobOpenForWrite *op_job;
  SftpHandle *handle;
  ReplaceData *data;
  GError *error;

  op_job = G_VFS_JOB_OPEN_FOR_WRITE (job);
  data = G_VFS_JOB (job)->backend_data;

  if (reply_type == SSH_FXP_STATUS)
    {
      error = NULL;
      if (error_from_status (job, reply, G_IO_ERROR_EXISTS, -1, &error))

        g_vfs_job_failed (job, G_IO_ERROR, G_IO_ERROR_FAILED,
                          _("Invalid reply received"));
      else if (error->code == G_IO_ERROR_EXISTS)
        {


          g_error_free (error);

          replace_create_temp (backend, op_job);
        }
      else if (data->set_ownership &&
	       error->code == G_IO_ERROR_PERMISSION_DENIED)
        {
          g_error_free (error);


	  if (!op_job->make_backup)
	    replace_truncate_original (backend, job);
	  else
	    {


	      g_vfs_job_failed (job, G_IO_ERROR,
				G_IO_ERROR_CANT_CREATE_BACKUP,
				_("backups not supported yet"));
	    }
        }
      else
        {
          g_vfs_job_failed_from_error (job, error);
          g_error_free (error);
        }
      return;
    }

  if (reply_type != SSH_FXP_HANDLE)
    {
      g_vfs_job_failed (job, G_IO_ERROR, G_IO_ERROR_FAILED,
                        _("Invalid reply received"));
      return;
    }

  handle = sftp_handle_new (reply);
  handle->filename = g_strdup (op_job->filename);
  handle->tempname = g_strdup (data->tempname);
  handle->permissions = data->permissions;
  handle->set_permissions = data->set_permissions;
  handle->make_backup = op_job->make_backup;

  g_vfs_job_open_for_write_set_handle (op_job, handle);
  g_vfs_job_open_for_write_set_can_seek (op_job, TRUE);
  g_vfs_job_open_for_write_set_can_truncate (op_job, TRUE);

  g_vfs_job_succeeded (job);
}

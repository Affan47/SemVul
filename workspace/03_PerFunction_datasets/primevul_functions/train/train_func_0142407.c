thunar_transfer_job_execute (ExoJob  *job,
                             GError **error)
{
  ThunarThumbnailCache *thumbnail_cache;
  ThunarTransferNode   *node;
  ThunarApplication    *application;
  ThunarJobResponse     response;
  ThunarTransferJob    *transfer_job = THUNAR_TRANSFER_JOB (job);
  GFileInfo            *info;
  gboolean              parent_exists;
  GError               *err = NULL;
  GList                *new_files_list = NULL;
  GList                *snext;
  GList                *sp;
  GList                *tnext;
  GList                *tp;
  GFile                *target_parent;
  gchar                *base_name;
  gchar                *parent_display_name;

  _thunar_return_val_if_fail (THUNAR_IS_TRANSFER_JOB (job), FALSE);
  _thunar_return_val_if_fail (error == NULL || *error == NULL, FALSE);

  if (exo_job_set_error_if_cancelled (job, error))
    return FALSE;

  exo_job_info_message (job, _("Collecting files..."));


  application = thunar_application_get ();
  thumbnail_cache = thunar_application_get_thumbnail_cache (application);
  g_object_unref (application);

  for (sp = transfer_job->source_node_list, tp = transfer_job->target_file_list;
       sp != NULL && tp != NULL && err == NULL;
       sp = snext, tp = tnext)
    {

      snext = sp->next;
      tnext = tp->next;


      node = sp->data;

      info = g_file_query_info (node->source_file,
                                G_FILE_ATTRIBUTE_STANDARD_DISPLAY_NAME,
                                G_FILE_QUERY_INFO_NOFOLLOW_SYMLINKS,
                                exo_job_get_cancellable (job),
                                &err);

      if (G_UNLIKELY (info == NULL))
        break;


      if (transfer_job->type == THUNAR_TRANSFER_JOB_MOVE
          && thunar_g_file_is_trashed (node->source_file))
        {

          exo_job_info_message (job, _("Trying to restore \"%s\""),
                                g_file_info_get_display_name (info));


          target_parent = g_file_get_parent (tp->data);


          if (target_parent != NULL)
            parent_exists = g_file_query_exists (target_parent, exo_job_get_cancellable (job));


          if (exo_job_set_error_if_cancelled (job, &err))
            {
              g_object_unref (target_parent);
              break;
            }

          if (target_parent != NULL && !parent_exists)
            {

              base_name = g_file_get_basename (target_parent);
              parent_display_name = g_filename_display_name (base_name);
              g_free (base_name);


              response = thunar_job_ask_create (THUNAR_JOB (job),
                                                _("The folder \"%s\" does not exist anymore but is "
                                                  "required to restore the file \"%s\" from the "
                                                  "trash"),
                                                parent_display_name,
                                                g_file_info_get_display_name (info));


              if (G_UNLIKELY (response == THUNAR_JOB_RESPONSE_CANCEL))
                {
                  g_object_unref (target_parent);
                  g_free (parent_display_name);
                  break;
                }


              if (!g_file_make_directory_with_parents (target_parent,
                                                       exo_job_get_cancellable (job),
                                                       &err))
                {
                  if (!exo_job_is_cancelled (job))
                    {
                      g_clear_error (&err);


                      g_set_error (&err, G_IO_ERROR, G_IO_ERROR_FAILED,
                                   _("Failed to restore the folder \"%s\""),
                                   parent_display_name);
                    }

                  g_object_unref (target_parent);
                  g_free (parent_display_name);
                  break;
                }


              g_free (parent_display_name);
            }

          if (target_parent != NULL)
            g_object_unref (target_parent);
        }

      if (transfer_job->type == THUNAR_TRANSFER_JOB_MOVE)
        {

          exo_job_info_message (job, _("Trying to move \"%s\""),
                                g_file_info_get_display_name (info));

          if (g_file_move (node->source_file, tp->data,
                           G_FILE_COPY_NOFOLLOW_SYMLINKS
                           | G_FILE_COPY_NO_FALLBACK_FOR_MOVE,
                           exo_job_get_cancellable (job),
                           NULL, NULL, &err))
            {

              thunar_thumbnail_cache_move_file (thumbnail_cache,
                                                node->source_file,
                                                tp->data);


              new_files_list = thunar_g_file_list_prepend (new_files_list, tp->data);


              thunar_transfer_node_free (node);
              g_object_unref (tp->data);


              transfer_job->source_node_list = g_list_delete_link (transfer_job->source_node_list, sp);
              transfer_job->target_file_list = g_list_delete_link (transfer_job->target_file_list, tp);
            }
          else if (!exo_job_is_cancelled (job))
            {
              g_clear_error (&err);


              exo_job_info_message (job, _("Could not move \"%s\" directly. "
                                           "Collecting files for copying..."),
                                    g_file_info_get_display_name (info));

              if (!thunar_transfer_job_collect_node (transfer_job, node, &err))
                {

                  g_object_unref (info);
                  break;
                }
            }
        }
      else if (transfer_job->type == THUNAR_TRANSFER_JOB_COPY)
        {
          if (!thunar_transfer_job_collect_node (THUNAR_TRANSFER_JOB (job), node, &err))
            break;
        }

      g_object_unref (info);
    }


  g_object_unref (thumbnail_cache);


  if (G_LIKELY (err == NULL))
    {

      for (sp = transfer_job->source_node_list, tp = transfer_job->target_file_list;
           sp != NULL && tp != NULL && err == NULL;
           sp = sp->next, tp = tp->next)
        {
          thunar_transfer_job_copy_node (transfer_job, sp->data, tp->data, NULL,
                                         &new_files_list, &err);
        }
    }


  if (G_UNLIKELY (err != NULL))
    {
      g_propagate_error (error, err);
      return FALSE;
    }
  else
    {
      thunar_job_new_files (THUNAR_JOB (job), new_files_list);
      thunar_g_file_list_free (new_files_list);
      return TRUE;
    }
}

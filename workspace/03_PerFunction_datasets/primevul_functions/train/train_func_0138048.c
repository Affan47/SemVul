g_file_make_directory_with_parents (GFile         *file,
                                    GCancellable  *cancellable,
                                    GError       **error)
{
  GFile *work_file = NULL;
  GList *list = NULL, *l;
  GError *my_error = NULL;

  g_return_val_if_fail (G_IS_FILE (file), FALSE);

  if (g_cancellable_set_error_if_cancelled (cancellable, error))
    return FALSE;


  g_file_make_directory (file, cancellable, &my_error);
  if (!g_error_matches (my_error, G_IO_ERROR, G_IO_ERROR_NOT_FOUND))
    {
      if (my_error)
        g_propagate_error (error, my_error);
      return my_error == NULL;
    }

  work_file = g_object_ref (file);


  while (g_error_matches (my_error, G_IO_ERROR, G_IO_ERROR_NOT_FOUND))
    {
      GFile *parent_file;

      parent_file = g_file_get_parent (work_file);
      if (parent_file == NULL)
        break;

      g_clear_error (&my_error);
      g_file_make_directory (parent_file, cancellable, &my_error);


      if (g_error_matches (my_error, G_IO_ERROR, G_IO_ERROR_EXISTS))
        g_clear_error (&my_error);

      g_object_unref (work_file);
      work_file = g_object_ref (parent_file);

      if (g_error_matches (my_error, G_IO_ERROR, G_IO_ERROR_NOT_FOUND))
        list = g_list_prepend (list, parent_file);
      else
        g_object_unref (parent_file);
    }


  for (l = list; my_error == NULL && l; l = l->next)
    {
      g_file_make_directory ((GFile *) l->data, cancellable, &my_error);
      if (g_error_matches (my_error, G_IO_ERROR, G_IO_ERROR_EXISTS))
        g_clear_error (&my_error);
    }

  if (work_file)
    g_object_unref (work_file);


  while (list != NULL)
    {
      g_object_unref ((GFile *) list->data);
      list = g_list_remove (list, list->data);
    }


  if (my_error != NULL)
    {
      g_propagate_error (error, my_error);
      return FALSE;
    }

  return g_file_make_directory (file, cancellable, error);
}

exo_die_editor_set_path (ExoDieEditor *editor,
                         const gchar  *path)
{
  g_return_if_fail (EXO_DIE_IS_EDITOR (editor));
  g_return_if_fail (g_utf8_validate (path, -1, NULL));


  if (!exo_str_is_equal (editor->path, path))
    {

      g_free (editor->path);
      editor->path = g_strdup (path);


      g_object_notify (G_OBJECT (editor), "path");
    }
}

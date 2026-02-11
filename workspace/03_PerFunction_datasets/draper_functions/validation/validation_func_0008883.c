open_project (GladeWindow *window, const gchar *path)
{
  GladeProject *project;

  project = glade_project_new ();

  add_project (window, project, TRUE);
  update_default_path (window, path);

  if (!glade_project_load_from_file (project, path))
    {
      do_close (window, project);

      recent_remove (window, path);
      return FALSE;
    }


  recent_add (window, glade_project_get_path (project));

  return TRUE;
}

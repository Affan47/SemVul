project_get_base_path(void)
{
	GeanyProject *project = app->project;

	if (project && NZV(project->base_path))
	{
		if (g_path_is_absolute(project->base_path))
			return g_strdup(project->base_path);
		else
		{
			gchar *path;
			gchar *dir = g_path_get_dirname(project->file_name);

			if (utils_str_equal(project->base_path, "./"))
				return dir;

			path = g_build_filename(dir, project->base_path, NULL);
			g_free(dir);
			return path;
		}
	}
	return NULL;
}

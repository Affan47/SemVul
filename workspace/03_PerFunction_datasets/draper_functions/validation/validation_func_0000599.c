glade_project_model_get_iter_for_object (GladeProject* project,
                                         GObject* object,
                                         GtkTreeIter* iter)
{
	g_assert (object);

	iter->stamp     = project->priv->stamp;
	iter->user_data = object;
}

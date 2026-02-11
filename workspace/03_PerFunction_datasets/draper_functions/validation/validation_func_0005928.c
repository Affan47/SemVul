file_remove (GkmFileTracker *tracker, const gchar *path, GkmXdgModule *self)
{
	GkmObject *object;

	g_return_if_fail (path);
	g_return_if_fail (GKM_IS_XDG_MODULE (self));

	object = g_hash_table_lookup (self->objects_by_path, path);
	if (object != NULL)
		remove_object_from_module (self, object, path, NULL);
}

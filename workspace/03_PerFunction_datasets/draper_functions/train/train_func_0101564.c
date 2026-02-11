pk_backend_spawn_finalize (GObject *object)
{
	PkBackendSpawn *backend_spawn;

	g_return_if_fail (PK_IS_BACKEND_SPAWN (object));

	backend_spawn = PK_BACKEND_SPAWN (object);

	if (backend_spawn->priv->kill_id > 0)
		g_source_remove (backend_spawn->priv->kill_id);

	g_free (backend_spawn->priv->name);
	g_object_unref (backend_spawn->priv->conf);
	g_object_unref (backend_spawn->priv->spawn);
	if (backend_spawn->priv->backend != NULL)
		g_object_unref (backend_spawn->priv->backend);

	G_OBJECT_CLASS (pk_backend_spawn_parent_class)->finalize (object);
}

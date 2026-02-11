gtk_source_language_finalize (GObject *object)
{
	GtkSourceLanguage *lang;

	lang = GTK_SOURCE_LANGUAGE (object);

	if (lang->priv->ctx_data != NULL)
		g_critical ("context data not freed in gtk_source_language_finalize");

	g_free (lang->priv->lang_file_name);
	g_free (lang->priv->translation_domain);
	g_free (lang->priv->name);
	g_free (lang->priv->section);
	g_free (lang->priv->id);
	g_hash_table_destroy (lang->priv->properties);

	g_hash_table_destroy (lang->priv->styles);

	G_OBJECT_CLASS (gtk_source_language_parent_class)->finalize (object);
}

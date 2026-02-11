cg_window_finalize (GObject *object)
{
	CgWindow *window;
	CgWindowPrivate *priv;

	window = CG_WINDOW (object);
	priv = CG_WINDOW_PRIVATE (window);

	if (priv->editor_cc != NULL)
		g_object_unref (G_OBJECT (priv->editor_cc));
	if (priv->editor_go_members != NULL)
		g_object_unref (G_OBJECT (priv->editor_go_members));
	if (priv->editor_go_properties != NULL)
		g_object_unref (G_OBJECT (priv->editor_go_properties));
	if (priv->editor_go_signals != NULL)
		g_object_unref (G_OBJECT (priv->editor_go_signals));
	if (priv->editor_py_methods != NULL)
		g_object_unref (G_OBJECT (priv->editor_py_methods));
	if (priv->editor_py_constvars != NULL)
		g_object_unref (G_OBJECT (priv->editor_py_constvars));
	if (priv->editor_js_methods != NULL)
		g_object_unref (G_OBJECT (priv->editor_js_methods));
	if (priv->editor_js_variables != NULL)
		g_object_unref (G_OBJECT (priv->editor_js_variables));
	if (priv->editor_js_imports != NULL)
		g_object_unref (G_OBJECT (priv->editor_js_imports));
	if (priv->editor_vala_methods != NULL)
		g_object_unref (G_OBJECT (priv->editor_vala_methods));
	if (priv->editor_vala_properties != NULL)
		g_object_unref (G_OBJECT (priv->editor_vala_properties));
	if (priv->editor_vala_signals != NULL)
		g_object_unref (G_OBJECT (priv->editor_vala_signals));

	if (priv->validator != NULL)
		g_object_unref (G_OBJECT (priv->validator));

	if (priv->bxml != NULL)
		g_object_unref (G_OBJECT (priv->bxml));

	gtk_widget_destroy(priv->window);

	G_OBJECT_CLASS (parent_class)->finalize (object);
}

gdata_access_rule_set_scope (GDataAccessRule *self, const gchar *type, const gchar *value)
{
	g_return_if_fail (GDATA_IS_ACCESS_RULE (self));
	g_return_if_fail (type != NULL);
	g_return_if_fail ((strcmp (type, GDATA_ACCESS_SCOPE_DEFAULT) == 0 && value == NULL) || value != NULL);

	g_free (self->priv->scope_type);
	self->priv->scope_type = g_strdup (type);

	g_free (self->priv->scope_value);
	self->priv->scope_value = g_strdup (value);

	g_object_freeze_notify (G_OBJECT (self));
	g_object_notify (G_OBJECT (self), "scope-type");
	g_object_notify (G_OBJECT (self), "scope-value");
	g_object_thaw_notify (G_OBJECT (self));
}

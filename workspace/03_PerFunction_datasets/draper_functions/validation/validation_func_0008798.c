update_one_secret (NMSetting *setting, const char *key, GValue *value, GError **error)
{
	GParamSpec *prop_spec;
	GValue transformed_value = { 0 };
	gboolean success = FALSE;

	prop_spec = g_object_class_find_property (G_OBJECT_GET_CLASS (setting), key);
	if (!prop_spec) {
		g_set_error (error,
		             NM_SETTING_ERROR,
		             NM_SETTING_ERROR_PROPERTY_NOT_FOUND,
		             "%s", key);
		return FALSE;
	}


	if (!(prop_spec->flags & NM_SETTING_PARAM_SECRET))
		return TRUE;

	if (g_value_type_compatible (G_VALUE_TYPE (value), G_PARAM_SPEC_VALUE_TYPE (prop_spec))) {
		g_object_set_property (G_OBJECT (setting), prop_spec->name, value);
		success = TRUE;
	} else if (g_value_transform (value, &transformed_value)) {
		g_object_set_property (G_OBJECT (setting), prop_spec->name, &transformed_value);
		g_value_unset (&transformed_value);
		success = TRUE;
	} else {
		g_set_error (error,
		             NM_SETTING_ERROR,
		             NM_SETTING_ERROR_PROPERTY_TYPE_MISMATCH,
		             "%s", key);
	}
	return success;
}

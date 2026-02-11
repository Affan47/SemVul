midgard_reflector_object_is_mixin (const gchar *classname)
{
	g_return_val_if_fail (classname != NULL, FALSE);

	GType class_type  = g_type_from_name (classname);
	if (class_type == G_TYPE_INVALID)
		return FALSE;

	return g_type_is_a (class_type, MIDGARD_TYPE_BASE_MIXIN);
}

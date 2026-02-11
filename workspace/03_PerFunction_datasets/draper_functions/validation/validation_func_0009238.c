midgard_object_is_approved(MidgardObject *self)
{
	g_assert(self != NULL);

	g_object_ref(self);

	MidgardConnection *mgd = MGD_OBJECT_CNC(self);
	MIDGARD_ERRNO_SET(mgd, MGD_ERR_OK);

	MidgardMetadata *metadata = MGD_DBOBJECT_METADATA (self);

	if (metadata->priv->approve_is_set)
		return metadata->priv->is_approved;

	GString *where = g_string_new("");
	g_string_append_printf(where, "guid = '%s' ", MGD_OBJECT_GUID(self));

	GValue *aval =
		midgard_core_query_get_field_value(mgd,
				"metadata_isapproved",
				midgard_core_class_get_table(MIDGARD_DBOBJECT_GET_CLASS(self)),
				where->str);

	g_string_free(where, TRUE);

	if (!aval) {

		g_object_unref(self);
		return FALSE;
	}

	gboolean av = FALSE;
	MIDGARD_GET_BOOLEAN_FROM_VALUE(av, aval)

	metadata->priv->approve_is_set = TRUE;
	metadata->priv->is_approved = av;

	g_value_unset(aval);
	g_free(aval);

	g_object_unref(self);

	return av;
}

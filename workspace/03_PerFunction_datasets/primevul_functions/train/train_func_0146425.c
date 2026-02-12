ves_icall_System_Reflection_FieldInfo_internal_from_handle_type (MonoClassField *handle, MonoType *type)
{
	gboolean found = FALSE;
	MonoClass *klass;
	MonoClass *k;

	g_assert (handle);

	if (!type) {
		klass = handle->parent;
	} else {
		klass = mono_class_from_mono_type (type);


		for (k = klass; k; k = k->parent) {
			if (k == handle->parent) {
				found = TRUE;
				break;
			}
		}

		if (!found)

			return NULL;
	}

	return mono_field_get_object (mono_domain_get (), klass, handle);
}

mono_class_get_virtual_methods (MonoClass* klass, gpointer *iter)
{
	MonoMethod** method;
	if (!iter)
		return NULL;
	if (klass->methods || !MONO_CLASS_HAS_STATIC_METADATA (klass)) {
		if (!*iter) {
			mono_class_setup_methods (klass);


			if (!klass->methods)
				return NULL;

			method = &klass->methods [0];
		} else {
			method = *iter;
			method++;
		}
		while (method < &klass->methods [klass->method.count]) {
			if (*method && ((*method)->flags & METHOD_ATTRIBUTE_VIRTUAL))
				break;
			method ++;
		}
		if (method < &klass->methods [klass->method.count]) {
			*iter = method;
			return *method;
		} else {
			return NULL;
		}
	} else {

		MonoMethod *res = NULL;
		int i, start_index;

		if (!*iter) {
			start_index = 0;
		} else {
			start_index = GPOINTER_TO_UINT (*iter);
		}

		for (i = start_index; i < klass->method.count; ++i) {
			guint32 flags;


			flags = mono_metadata_decode_table_row_col (klass->image, MONO_TABLE_METHOD, klass->method.first + i, MONO_METHOD_FLAGS);

			if (flags & METHOD_ATTRIBUTE_VIRTUAL)
				break;
		}

		if (i < klass->method.count) {
			res = mono_get_method (klass->image, MONO_TOKEN_METHOD_DEF | (klass->method.first + i + 1), klass);

			*iter = GUINT_TO_POINTER (i + 1);
			return res;
		} else {
			return NULL;
		}
	}
}

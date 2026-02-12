static gboolean
verify_class_for_overlapping_reference_fields (MonoClass *class)
{
	int i = 0, j;
	gpointer iter = NULL;
	MonoClassField *field;
	gboolean is_fulltrust = mono_verifier_is_class_full_trust (class);

	if (!((class->flags & TYPE_ATTRIBUTE_LAYOUT_MASK) == TYPE_ATTRIBUTE_EXPLICIT_LAYOUT))
		return TRUE;


	while ((field = mono_class_get_fields (class, &iter))) {
		int fieldEnd = get_field_end (field);
		gboolean is_valuetype = !MONO_TYPE_IS_REFERENCE (field->type);
		++i;

		if (mono_field_is_deleted (field) || (field->type->attrs & FIELD_ATTRIBUTE_STATIC))
			continue;

		for (j = i; j < class->field.count; ++j) {
			MonoClassField *other = &class->fields [j];
			int otherEnd = get_field_end (other);
			if (mono_field_is_deleted (other) || (is_valuetype && !MONO_TYPE_IS_REFERENCE (other->type)) || (other->type->attrs & FIELD_ATTRIBUTE_STATIC))
				continue;

			if (!is_valuetype && MONO_TYPE_IS_REFERENCE (other->type) && field->offset == other->offset && is_fulltrust)
				continue;

			if ((otherEnd > field->offset && otherEnd <= fieldEnd) || (other->offset >= field->offset && other->offset < fieldEnd))
				return FALSE;
		}
	}
	return TRUE;
}

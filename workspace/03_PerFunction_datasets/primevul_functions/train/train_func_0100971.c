static int
get_field_end (MonoClassField *field)
{
	int align;
	int size = mono_type_size (field->type, &align);
	if (size == 0)
		size = 4;
	return size + field->offset;
}

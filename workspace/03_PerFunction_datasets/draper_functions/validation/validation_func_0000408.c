bt_struct_declaration_get_field_from_index(struct declaration_struct *struct_declaration,
					 int index)
{
	if (index < 0)
		return NULL;
	return &g_array_index(struct_declaration->fields, struct declaration_field, index);
}

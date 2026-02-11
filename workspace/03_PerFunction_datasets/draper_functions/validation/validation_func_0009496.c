midgard_core_schema_type_validate_fields (MgdSchemaTypeAttr *type)
{
	g_assert (type != NULL);

	if (type->table == NULL)
		return;

	g_hash_table_foreach (type->prophash, __check_field_duplicates, type);
}

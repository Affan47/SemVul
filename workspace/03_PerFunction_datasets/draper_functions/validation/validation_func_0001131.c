jclass_attribute_container_has_attribute(const AttributeContainer* container,
	const char* attribute_name, const ConstantPool* constant_pool)
{
	int is_synthetic;
	char* attr_name;
	UTF8Entry* attr_info;

	if(container == NULL)
		return 0;

	attr_info = constant_pool->entries[container->name_index].info.utf8;
	attr_name = jclass_utf8_to_string(attr_info->contents, attr_info->length);

	is_synthetic = !strcmp(attribute_name, attr_name);
	free(attr_name);

	return is_synthetic;
}

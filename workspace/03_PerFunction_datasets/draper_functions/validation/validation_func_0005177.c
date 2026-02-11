_get_exception_store_type(const char *name)
{
	struct dm_exception_store_type *type;

	spin_lock(&_lock);

	type = __find_exception_store_type(name);

	if (type && !try_module_get(type->module))
		type = NULL;

	spin_unlock(&_lock);

	return type;
}

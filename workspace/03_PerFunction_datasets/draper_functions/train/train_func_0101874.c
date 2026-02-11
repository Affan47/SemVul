vm_class_is_anonymous(const struct vm_class *vmc)
{
	if (!vm_class_is_regular_class(vmc))
		return false;

	if (vm_class_is_abstract(vmc))
		return false;

	char *separator = strchr(vmc->name, '$');
	if (!separator)
		return false;

	size_t len = strlen(separator);
	if (len == 0)
		return false;

	return is_numeric(separator + 1);
}

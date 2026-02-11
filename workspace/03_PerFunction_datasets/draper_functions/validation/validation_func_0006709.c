create_dev_if_not_present(const char *name)
{
	struct stat st;
	dev_t dev;

	if (stat(name, &st) == 0)
		return;
	dev = name_to_dev_t(name);
	if (dev)
		(void) create_dev(name, dev);
}

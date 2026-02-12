static struct kobject *base_probe(dev_t dev, int *part, void *data)
{
	if (request_module("char-major-%d-%d", MAJOR(dev), MINOR(dev)) > 0)

		request_module("char-major-%d", MAJOR(dev));
	return NULL;
}

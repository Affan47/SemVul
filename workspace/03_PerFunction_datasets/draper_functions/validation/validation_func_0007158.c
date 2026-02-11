show(struct kobject *kobj, struct attribute *attr, char *buf)
{
	struct threshold_block *b = to_block(kobj);
	struct threshold_attr *a = to_attr(attr);
	ssize_t ret;

	ret = a->show ? a->show(b, buf) : -EIO;

	return ret;
}

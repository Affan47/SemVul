sysfs_do_create_link(struct kobject *kobj, struct kobject *target,
				const char *name, int warn)
{
	struct kernfs_node *parent = NULL;

	if (!kobj)
		parent = sysfs_root_kn;
	else
		parent = kobj->sd;

	if (!parent)
		return -EFAULT;

	return sysfs_do_create_link_sd(parent, target, name, warn);
}

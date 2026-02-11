param_attr_store(struct module_attribute *mattr,
				struct module_kobject *mk,
				const char *buf, size_t len)
{
 	int err;
	struct param_attribute *attribute = to_param_attr(mattr);

	if (!attribute->param->ops->set)
		return -EPERM;

	kernel_param_lock(mk->mod);
	param_check_unsafe(attribute->param);
	err = attribute->param->ops->set(buf, attribute->param);
	kernel_param_unlock(mk->mod);
	if (!err)
		return len;
	return err;
}

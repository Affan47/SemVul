read_live_nvram(struct file *file, struct kobject *kobj,
			       struct bin_attribute *attr,
			       char *buf, loff_t off, size_t count)
{
	struct esas2r_adapter *a = esas2r_adapter_from_kobj(kobj);
	int length = min_t(size_t, sizeof(struct esas2r_sas_nvram), PAGE_SIZE);

	memcpy(buf, a->nvram, length);
	return length;
}

gsmi_clear_eventlog_store(struct kobject *kobj,
					 struct kobj_attribute *attr,
					 const char *buf, size_t count)
{
	int rc;
	unsigned long flags;
	unsigned long val;
	struct {
		u32 percentage;
		u32 data_type;
	} param;

	rc = kstrtoul(buf, 0, &val);
	if (rc)
		return rc;


	if (val > 100)
		return -EINVAL;


	param.percentage = val;
	param.data_type = 0;

	spin_lock_irqsave(&gsmi_dev.lock, flags);


	memset(gsmi_dev.param_buf->start, 0, gsmi_dev.param_buf->length);
	memcpy(gsmi_dev.param_buf->start, &param, sizeof(param));

	rc = gsmi_exec(GSMI_CALLBACK, GSMI_CMD_CLEAR_EVENT_LOG);

	spin_unlock_irqrestore(&gsmi_dev.lock, flags);

	if (rc)
		return rc;
	return count;
}

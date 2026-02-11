fnic_trace_ctrl_read(struct file *filp,
				  char __user *ubuf,
				  size_t cnt, loff_t *ppos)
{
	char buf[64];
	int len;
	u8 *trace_type;
	len = 0;
	trace_type = (u8 *)filp->private_data;
	if (*trace_type == fc_trc_flag->fnic_trace)
		len = sprintf(buf, "%u\n", fnic_tracing_enabled);
	else if (*trace_type == fc_trc_flag->fc_trace)
		len = sprintf(buf, "%u\n", fnic_fc_tracing_enabled);
	else if (*trace_type == fc_trc_flag->fc_clear)
		len = sprintf(buf, "%u\n", fnic_fc_trace_cleared);
	else
		pr_err("fnic: Cannot read to any debugfs file\n");

	return simple_read_from_buffer(ubuf, cnt, ppos, buf, len);
}

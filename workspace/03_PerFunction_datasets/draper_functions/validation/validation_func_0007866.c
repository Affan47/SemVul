fdisk_write_disklabel(struct fdisk_context *cxt)
{
	if (!cxt || !cxt->label || cxt->readonly)
		return -EINVAL;
	if (!cxt->label->op->write)
		return -ENOSYS;
	return cxt->label->op->write(cxt);
}

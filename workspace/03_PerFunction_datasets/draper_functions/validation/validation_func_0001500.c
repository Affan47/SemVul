edd_show_info_flags(struct edd_device *edev, char *buf)
{
	struct edd_info *info;
	char *p = buf;
	if (!edev)
		return -EINVAL;
	info = edd_dev_get_info(edev);
	if (!info || !buf)
		return -EINVAL;

	if (info->params.info_flags & EDD_INFO_DMA_BOUNDARY_ERROR_TRANSPARENT)
		p += scnprintf(p, left, "DMA boundary error transparent\n");
	if (info->params.info_flags & EDD_INFO_GEOMETRY_VALID)
		p += scnprintf(p, left, "geometry valid\n");
	if (info->params.info_flags & EDD_INFO_REMOVABLE)
		p += scnprintf(p, left, "removable\n");
	if (info->params.info_flags & EDD_INFO_WRITE_VERIFY)
		p += scnprintf(p, left, "write verify\n");
	if (info->params.info_flags & EDD_INFO_MEDIA_CHANGE_NOTIFICATION)
		p += scnprintf(p, left, "media change notification\n");
	if (info->params.info_flags & EDD_INFO_LOCKABLE)
		p += scnprintf(p, left, "lockable\n");
	if (info->params.info_flags & EDD_INFO_NO_MEDIA_PRESENT)
		p += scnprintf(p, left, "no media present\n");
	if (info->params.info_flags & EDD_INFO_USE_INT13_FN50)
		p += scnprintf(p, left, "use int13 fn50\n");
	return (p - buf);
}

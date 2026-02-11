show_plat_type(struct device *dev,
			      struct device_attribute *attr, char *buf)
{
	struct platform_device *plat_dev = to_platform_device(dev);
	struct niu_parent *p = dev_get_platdata(&plat_dev->dev);
	const char *type_str;

	switch (p->plat_type) {
	case PLAT_TYPE_ATLAS:
		type_str = "atlas";
		break;
	case PLAT_TYPE_NIU:
		type_str = "niu";
		break;
	case PLAT_TYPE_VF_P0:
		type_str = "vf_p0";
		break;
	case PLAT_TYPE_VF_P1:
		type_str = "vf_p1";
		break;
	default:
		type_str = "unknown";
		break;
	}

	return sprintf(buf, "%s\n", type_str);
}

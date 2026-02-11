snd_config_get_ctl_elem_enumerated(snd_config_t *n, snd_ctl_t *ctl,
					      snd_ctl_elem_info_t *info)
{
	const char *str;
	long val;
	unsigned int idx, items;
	switch (snd_config_get_type(n)) {
	case SND_CONFIG_TYPE_INTEGER:
		snd_config_get_integer(n, &val);
		return val;
	case SND_CONFIG_TYPE_STRING:
		snd_config_get_string(n, &str);
		break;
	default:
		return -1;
	}
	items = snd_ctl_elem_info_get_items(info);
	for (idx = 0; idx < items; idx++) {
		int err;
		snd_ctl_elem_info_set_item(info, idx);
		err = snd_ctl_elem_info(ctl, info);
		if (err < 0) {
			SNDERR("Cannot obtain info for CTL elem");
			return err;
		}
		if (strcmp(str, snd_ctl_elem_info_get_item_name(info)) == 0)
			return idx;
	}
	return -1;
}

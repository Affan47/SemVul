aim_putcap(aim_bstream_t *bs, fu32_t caps)
{
	int i;

	if (!bs)
		return -EINVAL;

	for (i = 0; aim_bstream_empty(bs); i++) {

		if (aim_caps[i].flag == AIM_CAPS_LAST)
			break;

		if (caps & aim_caps[i].flag)
			aimbs_putraw(bs, aim_caps[i].data, 0x10);

	}

	return 0;
}

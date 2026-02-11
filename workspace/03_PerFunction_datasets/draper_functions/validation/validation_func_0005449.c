name(struct lib_context *lc, struct ddf1 *ddf1, struct raid_dev *rd)
{
	int i, prefix;
	char buf[NAME_SIZE];
	struct ddf1_phys_drive *pd;
	struct ddf1_virt_drive *vd;
	struct ddf1_config_record *cr;

	if (!(pd = get_phys_drive(ddf1)))
		return err_phys_drive(lc, rd->di);

	i = get_config_byoffset(ddf1, pd, rd->offset);
	cr = get_config(ddf1, pd, i);
	if (i < 0 || !cr) {
		sprintf(buf, DDF1_SPARES);
		goto out;
	}

	if (!(vd = get_virt_drive(ddf1, cr)))
		return err_virt_drive(lc, rd->di);

	sprintf(buf, "%s_", handler);
	prefix = strlen(buf);

	if (vd->name[0]) {
		memcpy(buf + prefix, vd->name, 16);
		i = prefix + 16;
		while (!isgraph(buf[--i]));
		buf[i + 1] = 0;
	} else {
		char *b;

		for (b = buf + prefix, i = 0; i < 24; b += 8, i += 4)
			sprintf(b, "%02x%02x%02x%02x",
				vd->guid[i], vd->guid[i + 1],
				vd->guid[i + 2], vd->guid[i + 3]);


		if (!strncmp((char *) vd->guid, "LSI", 3))
			strncpy(buf + prefix + 32, "47114711", 8);
	}

out:
	return dbg_strdup(buf);
}

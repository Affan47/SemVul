_metadatalv_disp(struct dm_report *rh, struct dm_pool *mem __attribute__((unused)),
			    struct dm_report_field *field,
			    const void *data, void *private __attribute__((unused)))
{
	const struct logical_volume *lv = (const struct logical_volume *) data;

	if (lv_is_thin_pool(lv))
		return _lvname_disp(rh, mem, field,
				    first_seg(lv)->metadata_lv, private);

	dm_report_field_set_value(field, "", NULL);
	return 1;
}

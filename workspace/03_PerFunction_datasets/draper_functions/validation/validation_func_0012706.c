setup_default_blist (struct config * conf)
{
	struct blentry * ble;
	struct hwentry *hwe;
	char * str;
	int i;

	str = STRDUP("^(ram|raw|loop|fd|md|dm-|sr|scd|st)[0-9]*");
	if (!str)
		return 1;
	if (store_ble(conf->blist_devnode, str, ORIGIN_DEFAULT))
		return 1;

	str = STRDUP("^hd[a-z]");
	if (!str)
		return 1;
	if (store_ble(conf->blist_devnode, str, ORIGIN_DEFAULT))
		return 1;

	str = STRDUP("^dcssblk[0-9]*");
	if (!str)
		return 1;
	if (store_ble(conf->blist_devnode, str, ORIGIN_DEFAULT))
		return 1;

	str = STRDUP("^cciss!c[0-9]d[0-9]*");
	if (!str)
		return 1;
	if (store_ble(conf->blist_devnode, str, ORIGIN_DEFAULT))
		return 1;

	str = STRDUP("^nvme.*");
	if (!str)
		return 1;
	if (store_ble(conf->blist_devnode, str, ORIGIN_DEFAULT))
		return 1;

	vector_foreach_slot (conf->hwtable, hwe, i) {
		if (hwe->bl_product) {
			if (alloc_ble_device(conf->blist_device))
				return 1;
			ble = VECTOR_SLOT(conf->blist_device,
					  VECTOR_SIZE(conf->blist_device) -1);
			if (set_ble_device(conf->blist_device,
					   STRDUP(hwe->vendor),
					   STRDUP(hwe->bl_product),
					   ORIGIN_DEFAULT)) {
				FREE(ble);
				return 1;
			}
		}
	}
	return 0;
}

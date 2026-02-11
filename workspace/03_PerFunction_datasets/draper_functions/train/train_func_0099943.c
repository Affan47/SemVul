hdhomerun_device_tuner_lockkey_release(struct hdhomerun_device_t *hd)
{
	if (hd->multicast_ip != 0) {
		return 1;
	}
	if (!hd->cs) {
		hdhomerun_debug_printf(hd->dbg, "hdhomerun_device_tuner_lockkey_release: device not set\n");
		return -1;
	}

	if (hd->lockkey == 0) {
		return 1;
	}

	char name[32];
	hdhomerun_sprintf(name, name + sizeof(name), "/tuner%u/lockkey", hd->tuner);
	int ret = hdhomerun_control_set_with_lockkey(hd->cs, name, "none", hd->lockkey, NULL, NULL);

	hd->lockkey = 0;
	return ret;
}

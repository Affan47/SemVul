hdhomerun_device_set_tuner_channel(struct hdhomerun_device_t *hd, const char *channel)
{
	if (!hd->cs) {
		hdhomerun_debug_printf(hd->dbg, "hdhomerun_device_set_tuner_channel: device not set\n");
		return -1;
	}

	char name[32];
	hdhomerun_sprintf(name, name + sizeof(name), "/tuner%u/channel", hd->tuner);
	return hdhomerun_control_set_with_lockkey(hd->cs, name, channel, hd->lockkey, NULL, NULL);
}

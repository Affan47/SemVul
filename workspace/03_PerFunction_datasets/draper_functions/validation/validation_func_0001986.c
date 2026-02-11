suicide_new(const char * subplugin)
{
	struct pluginDevice*	sd = ST_MALLOCT(struct pluginDevice);

	if (sd == NULL) {
		LOG(PIL_CRIT, "out of memory");
		return(NULL);
	}
	memset(sd, 0, sizeof(*sd));
	sd->pluginid = pluginid;
	sd->idinfo = DEVICE;
	sd->sp.s_ops = &suicideOps;
	return &(sd->sp);
}

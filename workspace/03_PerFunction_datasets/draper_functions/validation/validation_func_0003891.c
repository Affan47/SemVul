apcsmart_hostlist(StonithPlugin * s)
{
	struct pluginDevice *ad = (struct pluginDevice *) s;

	if (Debug) {
		LOG(PIL_DEBUG, "%s: called.", __FUNCTION__);
	}
	ERRIFNOTCONFIGED(s,NULL);

	return OurImports->CopyHostList((const char **)(void*)ad->hostlist);
}

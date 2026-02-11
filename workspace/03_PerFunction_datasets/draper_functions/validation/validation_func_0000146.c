init_bridge_processor (SgenBridgeProcessor *processor, const char *name)
{
	if (!strcmp ("old", name)) {
		memset (processor, 0, sizeof (SgenBridgeProcessor));
		sgen_old_bridge_init (processor);
	} else if (!strcmp ("new", name)) {
		memset (processor, 0, sizeof (SgenBridgeProcessor));
		sgen_new_bridge_init (processor);
	} else if (!strcmp ("tarjan", name)) {
		memset (processor, 0, sizeof (SgenBridgeProcessor));
		sgen_tarjan_bridge_init (processor);
	} else {
		return FALSE;
	}
	return TRUE;
}

proto_register_plugin(const proto_plugin *plug)
{
	if (!plug) {

		return;
	}
	dissector_plugins = g_slist_prepend(dissector_plugins, (proto_plugin *)plug);
}

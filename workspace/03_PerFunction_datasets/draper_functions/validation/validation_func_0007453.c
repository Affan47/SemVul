upnp_ctrl_launch(const upnp_service_t *usd, const char *action,
	nv_pair_t **argv, size_t argc, upnp_ctrl_cb_t cb, void *cb_arg,
	upnp_ctrl_launch_cb_t launch_cb)
{
	upnp_ctrl_t *ucd;
	xnode_t *root;
	size_t i;
	soap_rpc_t *sr;

	g_assert(usd != NULL);
	g_assert(action != NULL);
	g_assert(0 == argc || argv != NULL);

	WALLOC0(ucd);
	ucd->magic = UPNP_CTRL_MAGIC;
	ucd->lcb = launch_cb;
	ucd->cb = cb;
	ucd->cb_arg = cb_arg;


	{
		char ns[256];

		str_bprintf(ns, sizeof ns, "%s%s:%u",
			UPNP_NS_BASE,
			upnp_service_type_to_string(upnp_service_type(usd)),
			upnp_service_version(usd));

		root = xnode_new_element(NULL, ns, action);
		xnode_add_namespace(root, UPNP_PREFIX, ns);
	}


	for (i = 0; i < argc; i++) {
		nv_pair_t *nv = argv[i];
		xnode_t *xargs;

		xargs = xnode_new_element(root, NULL, nv_pair_name(nv));
		xnode_new_text(xargs, nv_pair_value_str(nv), FALSE);
	}


	{
		char action_uri[256];
		uint32 options = SOAP_RPC_O_MAN_RETRY | SOAP_RPC_O_ALL_CAPS;


		if (host_addr_net(upnp_get_local_addr()) == NET_TYPE_NONE)
			options |= SOAP_RPC_O_LOCAL_ADDR;

		str_bprintf(action_uri, sizeof action_uri, "%s#%s",
			xnode_element_ns(root), action);

		ucd->action = atom_str_get(action_uri);

		sr = soap_rpc(upnp_service_control_url(usd), action_uri,
			UPNP_REPLY_MAXSIZE, options, root, UPNP_SOAP_PREFIX,
			upnp_ctrl_soap_reply, upnp_ctrl_soap_error, ucd);
	}


	for (i = 0; i < argc; i++) {
		nv_pair_free_null(&argv[i]);
	}


	if (NULL == sr) {
		if (GNET_PROPERTY(upnp_debug)) {
			g_warning("UPNP SOAP RPC \"%s\" to \"%s\" not launched: "
				"payload is too large", action, upnp_service_control_url(usd));
		}
		upnp_ctrl_free(ucd);
		return NULL;
	}

	ucd->sr = sr;

	return ucd;
}

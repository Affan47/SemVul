Protocol_SSID_enable(PROTO_ENABLE_PARMS) {

	for (Netracker::track_iter x = globalreg->netracker->tracked_map.begin();
		 x != globalreg->netracker->tracked_map.end(); ++x) {
		Netracker::tracked_network *net = x->second;

		int filtered = 0;

		if (net->type == network_remove)
			continue;


		if (globalreg->netracker->netcli_filter->RunFilter(net->bssid, mac_addr(0),
														   mac_addr(0)))
			continue;


		map<uint32_t, Netracker::adv_ssid_data *>::iterator asi;
		for (asi = net->ssid_map.begin(); asi != net->ssid_map.end(); ++asi) {
			if (globalreg->netracker->netcli_filter->RunPcreFilter(asi->second->ssid)) {
				filtered = 1;
				break;
			}
		}

		if (filtered)
			continue;

		for (asi = net->ssid_map.begin(); asi != net->ssid_map.end(); ++asi) {
			kis_protocol_cache cache;
			if (globalreg->kisnetserver->SendToClient(in_fd, _NPM(PROTO_REF_SSID),
													  (void *) asi->second,
													  &cache) < 0)
				break;
		}
	}
}

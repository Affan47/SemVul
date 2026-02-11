do_select6(void *input)
{
	struct client_state *client;
	struct dhc6_lease *lease;
	struct data_string ds;
	struct timeval tv;
	int send_ret;

	client = input;


	lease = client->selected_lease;
	if (lease == NULL || lease->bindings == NULL) {
		log_error("Illegal to attempt selection without selecting "
			  "a lease.");
		return;
	}

	switch(check_timing6(client, DHCPV6_REQUEST, "Request", lease, &ds)) {
	      case CHK_TIM_MRC_EXCEEDED:
	      case CHK_TIM_MRD_EXCEEDED:
		log_debug("PRC: Lease %s failed.",
			  print_hex_1(lease->server_id.len,
				      lease->server_id.data, 56));


		dhc6_lease_destroy(&lease, MDL);
		client->selected_lease = NULL;


		if (client->advertised_leases != NULL)
			start_selecting6(client);
		else
			start_init6(client);
		return;
	      case CHK_TIM_ALLOC_FAILURE:
		return;
	      case CHK_TIM_SUCCESS:
		break;
	}


	dhcpv6_universe.encapsulate(&ds, NULL, NULL, client,
				    NULL, client->sent_options, &global_scope,
				    &dhcpv6_universe);


	if (wanted_ia_na &&
	    dhc6_add_ia_na(client, &ds, lease,
			   DHCPV6_REQUEST) != ISC_R_SUCCESS) {
		data_string_forget(&ds, MDL);
		return;
	}
	if (wanted_ia_ta &&
	    dhc6_add_ia_ta(client, &ds, lease,
			   DHCPV6_REQUEST) != ISC_R_SUCCESS) {
		data_string_forget(&ds, MDL);
		return;
	}
	if (wanted_ia_pd &&
	    dhc6_add_ia_pd(client, &ds, lease,
			   DHCPV6_REQUEST) != ISC_R_SUCCESS) {
		data_string_forget(&ds, MDL);
		return;
	}

	log_info("XMT: Request on %s, interval %ld0ms.",
		 client->name ? client->name : client->interface->name,
		 (long int)client->RT);

	send_ret = send_packet6(client->interface,
				ds.data, ds.len, &DHCPv6DestAddr);
	if (send_ret != ds.len) {
		log_error("dhc6: send_packet6() sent %d of %d bytes",
			  send_ret, ds.len);
	}

	data_string_forget(&ds, MDL);


	tv.tv_sec = cur_tv.tv_sec + client->RT / 100;
	tv.tv_usec = cur_tv.tv_usec + (client->RT % 100) * 10000;
	if (tv.tv_usec >= 1000000) {
		tv.tv_sec += 1;
		tv.tv_usec -= 1000000;
	}
	add_timeout(&tv, do_select6, client, NULL, NULL);

	dhc6_retrans_advance(client);
}

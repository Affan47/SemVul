static stf_status informational(struct state *st, struct msg_digest *md)
{


	pexpect(st == md->st);
	st = md->st;

	struct payload_digest *const n_pld = md->chain[ISAKMP_NEXT_N];


	if (n_pld != NULL) {
		pb_stream *const n_pbs = &n_pld->pbs;
		struct isakmp_notification *const n =
			&n_pld->payload.notification;


		dbg("processing informational %s (%d)",
		    enum_name(&ikev1_notify_names, n->isan_type),
		    n->isan_type);

		pstats(ikev1_recv_notifies_e, n->isan_type);

		switch (n->isan_type) {


		case R_U_THERE:
			if (st == NULL) {
				plog_md(md, "received bogus  R_U_THERE informational message");
				return STF_IGNORE;
			}
			return dpd_inI_outR(st, n, n_pbs);

		case R_U_THERE_ACK:
			if (st == NULL) {
				plog_md(md, "received bogus R_U_THERE_ACK informational message");
				return STF_IGNORE;
			}
			return dpd_inR(st, n, n_pbs);

		case PAYLOAD_MALFORMED:
			if (st != NULL) {
				st->hidden_variables.st_malformed_received++;

				log_state(RC_LOG, st, "received %u malformed payload notifies",
					  st->hidden_variables.st_malformed_received);

				if (st->hidden_variables.st_malformed_sent >
				    MAXIMUM_MALFORMED_NOTIFY / 2 &&
				    ((st->hidden_variables.st_malformed_sent +
				      st->hidden_variables.
				      st_malformed_received) >
				     MAXIMUM_MALFORMED_NOTIFY)) {
					log_state(RC_LOG, st, "too many malformed payloads (we sent %u and received %u",
						  st->hidden_variables.st_malformed_sent,
						  st->hidden_variables.st_malformed_received);
					delete_state(st);
					md->st = st = NULL;
				}
			}

			return STF_IGNORE;

		case ISAKMP_N_CISCO_LOAD_BALANCE:


			if (st == NULL || !IS_ISAKMP_SA_ESTABLISHED(st->st_state)) {
				plog_md(md, "ignoring ISAKMP_N_CISCO_LOAD_BALANCE Informational Message with for unestablished state.");
			} else if (pbs_left(n_pbs) < 4) {
				log_state(RC_LOG_SERIOUS, st,
					  "ignoring ISAKMP_N_CISCO_LOAD_BALANCE Informational Message without IPv4 address");
			} else {


				struct in_addr in;
				memcpy(&in, n_pbs->roof - sizeof(in), sizeof(in));
				ip_address new_peer = address_from_in_addr(&in);


				if (address_is_any(&new_peer)) {
					ipstr_buf b;

					log_state(RC_LOG_SERIOUS, st,
						  "ignoring ISAKMP_N_CISCO_LOAD_BALANCE Informational Message with invalid IPv4 address %s",
						  ipstr(&new_peer, &b));
					return FALSE;
				}


				const char *tmp_name = st->st_connection->name;
				struct fd *tmp_whack_sock = dup_any(st->st_whack_sock);


				delete_state(st);
				md->st = st = NULL;


				struct connection *tmp_c = conn_by_name(tmp_name, false);

				if (DBGP(DBG_BASE)) {
					address_buf npb;
					DBG_log("new peer address: %s",
						str_address(&new_peer, &npb));


					int count_spd = 1;
					for (const struct spd_route *tmp_spd = &tmp_c->spd;
					     tmp_spd != NULL; tmp_spd = tmp_spd->spd_next) {
						address_buf b;
						endpoint_buf e;

						DBG_log("spd route number: %d",
							count_spd++);


						DBG_log("that id kind: %d",
							tmp_spd->that.id.kind);
						DBG_log("that id ipaddr: %s",
							str_address(&tmp_spd->that.id.ip_addr, &b));
						if (tmp_spd->that.id.name.ptr != NULL) {
							DBG_dump_hunk("that id name",
								      tmp_spd->that.id. name);
						}
						DBG_log("that host_addr: %s",
							str_endpoint(&tmp_spd->that.host_addr, &e));
						DBG_log("that nexthop: %s",
							str_address(&tmp_spd->that.host_nexthop, &b));
						DBG_log("that srcip: %s",
							str_address(&tmp_spd->that.host_srcip, &b));
						selector_buf sb;
						DBG_log("that client: %s",
							str_selector(&tmp_spd->that.client, &sb));
						DBG_log("that has_client: %d",
							tmp_spd->that.has_client);
						DBG_log("that has_client_wildcard: %d",
							tmp_spd->that.has_client_wildcard);
						DBG_log("that has_port_wildcard: %d",
							tmp_spd->that.has_port_wildcard);
						DBG_log("that has_id_wildcards: %d",
							tmp_spd->that.has_id_wildcards);
					}

					if (tmp_c->interface != NULL) {
						endpoint_buf b;
						DBG_log("Current interface_addr: %s",
							str_endpoint(&tmp_c->interface->local_endpoint, &b));
					}
				}


				ip_address old_addr = tmp_c->spd.that.host_addr;


				tmp_c->spd.that.host_addr = new_peer;


				dbg("Old host_addr_name : %s", tmp_c->spd.that.host_addr_name);
				tmp_c->spd.that.host_addr_name = NULL;


				tmp_c->spd.that.id.ip_addr = new_peer;


				ipstr_buf b;
				if (sameaddr(&tmp_c->spd.this.host_nexthop,
					     &old_addr)) {
					if (DBGP(DBG_BASE)) {
						DBG_log("this host's next hop %s was the same as the old remote addr",
							ipstr(&old_addr, &b));
						DBG_log("changing this host's next hop to %s",
							ipstr(&new_peer, &b));
					}
					tmp_c->spd.this.host_nexthop = new_peer;
				}

				if (sameaddr(&tmp_c->spd.that.host_srcip,
					     &old_addr)) {
					if (DBGP(DBG_BASE)) {
						DBG_log("Old that host's srcip %s was the same as the old remote addr",
							ipstr(&old_addr, &b));
						DBG_log("changing that host's srcip to %s",
							ipstr(&new_peer, &b));
					}
					tmp_c->spd.that.host_srcip = new_peer;
				}

				if (sameaddr(&tmp_c->spd.that.client.addr,
					     &old_addr)) {
					if (DBGP(DBG_BASE)) {
						DBG_log("Old that client ip %s was the same as the old remote address",
							ipstr(&old_addr, &b));
						DBG_log("changing that client's ip to %s",
							ipstr(&new_peer, &b));
					}
					tmp_c->spd.that.client.addr = new_peer;
				}


				tmp_c->host_pair->remote = endpoint(&new_peer,
								    endpoint_hport(&tmp_c->host_pair->remote));


				initiate_connections_by_name(tmp_name, NULL,
							     tmp_whack_sock,
							     tmp_whack_sock == NULL);
				close_any(&tmp_whack_sock);
			}
			return STF_IGNORE;
		default:
		{
			struct logger logger = st != NULL ? *(st->st_logger) : MESSAGE_LOGGER(md);
			log_message(RC_LOG_SERIOUS, &logger,
				    "received and ignored notification payload: %s",
				    enum_name(&ikev1_notify_names, n->isan_type));
			return STF_IGNORE;
		}
		}
	} else {

		if (md->chain[ISAKMP_NEXT_D] == NULL) {
			struct logger logger = st != NULL ? *(st->st_logger) : MESSAGE_LOGGER(md);
			log_message(RC_LOG_SERIOUS, &logger,
				    "received and ignored empty informational notification payload");
		}
		return STF_IGNORE;
	}
}

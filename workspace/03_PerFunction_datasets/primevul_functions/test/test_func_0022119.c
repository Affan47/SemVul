static int sctp_sf_check_restart_addrs(const struct sctp_association *new_asoc,
				       const struct sctp_association *asoc,
				       struct sctp_chunk *init,
				       sctp_cmd_seq_t *commands)
{
	struct sctp_transport *new_addr, *addr;
	int found;


	new_addr = NULL;
	found = 0;

	list_for_each_entry(new_addr, &new_asoc->peer.transport_addr_list,
			transports) {
		found = 0;
		list_for_each_entry(addr, &asoc->peer.transport_addr_list,
				transports) {
			if (sctp_cmp_addr_exact(&new_addr->ipaddr,
						&addr->ipaddr)) {
				found = 1;
				break;
			}
		}
		if (!found)
			break;
	}


	if (!found && new_addr) {
		sctp_sf_send_restart_abort(&new_addr->ipaddr, init, commands);
	}


	return found;
}

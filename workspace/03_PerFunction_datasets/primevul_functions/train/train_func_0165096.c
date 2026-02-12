void sctp_assoc_control_transport(struct sctp_association *asoc,
				  struct sctp_transport *transport,
				  sctp_transport_cmd_t command,
				  sctp_sn_error_t error)
{
	struct sctp_transport *t = NULL;
	struct sctp_transport *first;
	struct sctp_transport *second;
	struct sctp_ulpevent *event;
	struct sockaddr_storage addr;
	int spc_state = 0;


	switch (command) {
	case SCTP_TRANSPORT_UP:


		if (SCTP_UNCONFIRMED == transport->state &&
		    SCTP_HEARTBEAT_SUCCESS == error)
			spc_state = SCTP_ADDR_CONFIRMED;
		else
			spc_state = SCTP_ADDR_AVAILABLE;
		transport->state = SCTP_ACTIVE;
		break;

	case SCTP_TRANSPORT_DOWN:


		if (transport->state != SCTP_UNCONFIRMED)
			transport->state = SCTP_INACTIVE;

		spc_state = SCTP_ADDR_UNREACHABLE;
		break;

	default:
		return;
	}


	memset(&addr, 0, sizeof(struct sockaddr_storage));
	memcpy(&addr, &transport->ipaddr, transport->af_specific->sockaddr_len);
	event = sctp_ulpevent_make_peer_addr_change(asoc, &addr,
				0, spc_state, error, GFP_ATOMIC);
	if (event)
		sctp_ulpq_tail_event(&asoc->ulpq, event);


	first = NULL; second = NULL;

	list_for_each_entry(t, &asoc->peer.transport_addr_list,
			transports) {

		if ((t->state == SCTP_INACTIVE) ||
		    (t->state == SCTP_UNCONFIRMED))
			continue;
		if (!first || t->last_time_heard > first->last_time_heard) {
			second = first;
			first = t;
		}
		if (!second || t->last_time_heard > second->last_time_heard)
			second = t;
	}


	if (((asoc->peer.primary_path->state == SCTP_ACTIVE) ||
	     (asoc->peer.primary_path->state == SCTP_UNKNOWN)) &&
	    first != asoc->peer.primary_path) {
		second = first;
		first = asoc->peer.primary_path;
	}


	if (!first) {
		first = asoc->peer.primary_path;
		second = asoc->peer.primary_path;
	}


	asoc->peer.active_path = first;
	asoc->peer.retran_path = second;
}

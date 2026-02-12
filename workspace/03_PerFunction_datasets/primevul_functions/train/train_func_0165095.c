void sctp_assoc_update_retran_path(struct sctp_association *asoc)
{
	struct sctp_transport *t, *next;
	struct list_head *head = &asoc->peer.transport_addr_list;
	struct list_head *pos;

	if (asoc->peer.transport_count == 1)
		return;


	t = asoc->peer.retran_path;
	pos = &t->transports;
	next = NULL;

	while (1) {

		if (pos->next == head)
			pos = head->next;
		else
			pos = pos->next;

		t = list_entry(pos, struct sctp_transport, transports);


		if (t == asoc->peer.retran_path) {
			t = next;
			break;
		}


		if ((t->state == SCTP_ACTIVE) ||
		    (t->state == SCTP_UNKNOWN)) {
			break;
		} else {


			if (!next)
				next = t;
		}
	}

	asoc->peer.retran_path = t;

	SCTP_DEBUG_PRINTK_IPADDR("sctp_assoc_update_retran_path:association"
				 " %p addr: ",
				 " port: %d\n",
				 asoc,
				 (&t->ipaddr),
				 ntohs(t->ipaddr.v4.sin_port));
}

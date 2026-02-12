static int bgp_collision_detect(struct peer *new, struct in_addr remote_id)
{
	struct peer *peer;


	peer = new->doppelganger;
	if (peer == NULL)
		return 0;


	if (peer_established(peer) || peer->status == Clearing) {
		bgp_notify_send(new, BGP_NOTIFY_CEASE,
				BGP_NOTIFY_CEASE_COLLISION_RESOLUTION);
		return -1;
	}

	if ((peer->status != OpenConfirm) && (peer->status != OpenSent))
		return 0;


	if (ntohl(peer->local_id.s_addr) < ntohl(remote_id.s_addr)
	    || (ntohl(peer->local_id.s_addr) == ntohl(remote_id.s_addr)
		&& peer->local_as < peer->as))
		if (!CHECK_FLAG(peer->sflags, PEER_STATUS_ACCEPT_PEER)) {


			bgp_notify_send(peer, BGP_NOTIFY_CEASE,
					BGP_NOTIFY_CEASE_COLLISION_RESOLUTION);
			return 1;
		} else {
			bgp_notify_send(new, BGP_NOTIFY_CEASE,
					BGP_NOTIFY_CEASE_COLLISION_RESOLUTION);
			return -1;
		}
	else {
		if (ntohl(peer->local_id.s_addr) == ntohl(remote_id.s_addr)
		    && peer->local_as == peer->as)
			flog_err(EC_BGP_ROUTER_ID_SAME,
				 "Peer's router-id %pI4 is the same as ours",
				 &remote_id);


		if (CHECK_FLAG(peer->sflags, PEER_STATUS_ACCEPT_PEER)) {
			bgp_notify_send(peer, BGP_NOTIFY_CEASE,
					BGP_NOTIFY_CEASE_COLLISION_RESOLUTION);
			return 1;
		} else {
			bgp_notify_send(new, BGP_NOTIFY_CEASE,
					BGP_NOTIFY_CEASE_COLLISION_RESOLUTION);
			return -1;
		}
	}
}

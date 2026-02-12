bool bgp_notify_send_hard_reset(struct peer *peer, uint8_t code,
				uint8_t subcode)
{


	if (!bgp_has_graceful_restart_notification(peer))
		return false;


	if (code == BGP_NOTIFY_CEASE) {
		switch (subcode) {
		case BGP_NOTIFY_CEASE_MAX_PREFIX:
		case BGP_NOTIFY_CEASE_ADMIN_SHUTDOWN:
		case BGP_NOTIFY_CEASE_PEER_UNCONFIG:
		case BGP_NOTIFY_CEASE_HARD_RESET:
		case BGP_NOTIFY_CEASE_BFD_DOWN:
			return true;
		case BGP_NOTIFY_CEASE_ADMIN_RESET:


			if (CHECK_FLAG(peer->bgp->flags,
				       BGP_FLAG_HARD_ADMIN_RESET))
				return true;
			else
				return false;
		default:
			break;
		}
	}

	return false;
}

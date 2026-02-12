bool bgp_notify_received_hard_reset(struct peer *peer, uint8_t code,
				    uint8_t subcode)
{


	if (!bgp_has_graceful_restart_notification(peer))
		return false;

	if (code == BGP_NOTIFY_CEASE && subcode == BGP_NOTIFY_CEASE_HARD_RESET)
		return true;

	return false;
}

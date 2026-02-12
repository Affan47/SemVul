static void avrcp_connect_browsing(struct avrcp *session)
{


	if (avctp_is_initiator(session->conn)) {
		avctp_connect_browsing(session->conn);
		return;
	}

	if (session->browsing_timer > 0)
		return;

	session->browsing_timer = timeout_add_seconds(AVRCP_BROWSING_TIMEOUT,
							connect_browsing,
							session, NULL);
}

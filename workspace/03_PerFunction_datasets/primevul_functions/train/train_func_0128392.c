static uint32_t cli_session_setup_capabilities(struct cli_state *cli,
					       uint32_t sesssetup_capabilities)
{
	uint32_t client_capabilities = smb1cli_conn_capabilities(cli->conn);


	client_capabilities &= (SMB_CAP_BOTH_MASK | SMB_CAP_LEGACY_CLIENT_MASK);


	client_capabilities &= ~(CAP_DYNAMIC_REAUTH|CAP_EXTENDED_SECURITY);
	sesssetup_capabilities &= (CAP_DYNAMIC_REAUTH|CAP_EXTENDED_SECURITY);
	client_capabilities |= sesssetup_capabilities;

	return client_capabilities;
}

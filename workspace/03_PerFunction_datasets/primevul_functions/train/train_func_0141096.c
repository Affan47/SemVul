process_redirect_pdu(STREAM s, RD_BOOL enhanced_redirect  )
{
	uint32 len;
	uint16 redirect_identifier;


	g_redirect = True;
	free(g_redirect_server);
	free(g_redirect_username);
	free(g_redirect_domain);
	free(g_redirect_lb_info);
	free(g_redirect_cookie);

	g_redirect_server = NULL;
	g_redirect_username = NULL;
	g_redirect_domain = NULL;
	g_redirect_lb_info = NULL;
	g_redirect_cookie = NULL;


	in_uint8s(s, 2);


	if (enhanced_redirect)
	{

		in_uint16_le(s, redirect_identifier);
		if (redirect_identifier != 0x0400)
			error("Protocol error in server redirection, unexpected data.");


		in_uint8s(s, 2);


		in_uint32_le(s, g_redirect_session_id);
	}


	in_uint32_le(s, g_redirect_flags);

	if (g_redirect_flags & PDU_REDIRECT_HAS_IP)
	{

		in_uint32_le(s, len);


		rdp_in_unistr(s, len, &g_redirect_server, &g_redirect_server_len);
	}

	if (g_redirect_flags & PDU_REDIRECT_HAS_LOAD_BALANCE_INFO)
	{

		in_uint32_le(s, g_redirect_lb_info_len);


		if (g_redirect_lb_info != NULL)
			free(g_redirect_lb_info);

		g_redirect_lb_info = xmalloc(g_redirect_lb_info_len);


		in_uint8p(s, g_redirect_lb_info, g_redirect_lb_info_len);
	}

	if (g_redirect_flags & PDU_REDIRECT_HAS_USERNAME)
	{

		in_uint32_le(s, len);


		rdp_in_unistr(s, len, &g_redirect_username, &g_redirect_username_len);
	}

	if (g_redirect_flags & PDU_REDIRECT_HAS_DOMAIN)
	{

		in_uint32_le(s, len);


		rdp_in_unistr(s, len, &g_redirect_domain, &g_redirect_domain_len);
	}

	if (g_redirect_flags & PDU_REDIRECT_HAS_PASSWORD)
	{


		in_uint32_le(s, g_redirect_cookie_len);


		if (g_redirect_cookie != NULL)
			free(g_redirect_cookie);

		g_redirect_cookie = xmalloc(g_redirect_cookie_len);


		in_uint8p(s, g_redirect_cookie, g_redirect_cookie_len);
	}

	if (g_redirect_flags & PDU_REDIRECT_DONT_STORE_USERNAME)
	{
		warning("PDU_REDIRECT_DONT_STORE_USERNAME set\n");
	}

	if (g_redirect_flags & PDU_REDIRECT_USE_SMARTCARD)
	{
		warning("PDU_REDIRECT_USE_SMARTCARD set\n");
	}

	if (g_redirect_flags & PDU_REDIRECT_INFORMATIONAL)
	{


		g_redirect = False;
	}

	if (g_redirect_flags & PDU_REDIRECT_HAS_TARGET_FQDN)
	{
		in_uint32_le(s, len);


		if (g_redirect_server)
		{
			free(g_redirect_server);
			g_redirect_server = NULL;
		}


		rdp_in_unistr(s, len, &g_redirect_server, &g_redirect_server_len);
	}

	if (g_redirect_flags & PDU_REDIRECT_HAS_TARGET_NETBIOS)
	{
		warning("PDU_REDIRECT_HAS_TARGET_NETBIOS set\n");
	}

	if (g_redirect_flags & PDU_REDIRECT_HAS_TARGET_IP_ARRAY)
	{
		warning("PDU_REDIRECT_HAS_TARGET_IP_ARRAY set\n");
	}

	return True;
}

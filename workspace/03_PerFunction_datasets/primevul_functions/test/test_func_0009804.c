inbound_sasl_error (server *serv)
{
	if (serv->retry_sasl && !serv->sent_saslauth)
		return 1;


	if (!serv->sent_saslauth && serv->sasl_mech != MECH_EXTERNAL && serv->sasl_mech != MECH_PLAIN)
	{
		serv->sasl_mech -= 1;
		tcp_sendf (serv, "AUTHENTICATE %s\r\n", sasl_mechanisms[serv->sasl_mech]);
		return 1;
	}
	return 0;
}

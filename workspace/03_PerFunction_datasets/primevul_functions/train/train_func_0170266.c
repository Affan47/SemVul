static bool is_login_cmd_disabled(struct client *client)
{
	if (client->secured) {
		if (sasl_server_find_available_mech(client, "PLAIN") == NULL) {

			return TRUE;
		}
		return FALSE;
	}
	if (client->set->disable_plaintext_auth)
		return TRUE;
	if (strcmp(client->ssl_set->ssl, "required") == 0)
		return TRUE;
	return FALSE;
}

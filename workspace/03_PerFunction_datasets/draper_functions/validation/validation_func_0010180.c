previous_passphrase_handler(DBusMessageIter *iter,
					struct connman_service *service)
{
	enum connman_service_security security;
	struct previous_passphrase_data data;
	struct connman_network *network;

	network = __connman_service_get_network(service);
	data.passphrase = connman_network_get_string(network, "WiFi.PinWPS");

	if (connman_network_get_bool(network, "WiFi.UseWPS") == TRUE &&
						data.passphrase != NULL) {
		data.type = "wpspin";
	} else {
		data.passphrase = __connman_service_get_passphrase(service);
		if (data.passphrase == NULL)
			return;

		security = __connman_service_get_security(service);
		switch (security) {
		case CONNMAN_SERVICE_SECURITY_WEP:
			data.type = "wep";
			break;
		case CONNMAN_SERVICE_SECURITY_PSK:
			data.type  = "psk";
			break;


		default:
			break;
		}
	}

	connman_dbus_dict_append_dict(iter, "PreviousPassphrase",
			request_input_append_previouspassphrase, &data);
}

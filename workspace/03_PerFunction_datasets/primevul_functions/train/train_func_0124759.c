static GList *get_dhcpv6_option_value_list(GDHCPClient *dhcp_client,
					int code, int len,
					unsigned char *value,
					uint16_t *status)
{
	GList *list = NULL;
	char *str;
	int i;

	if (!value)
		return NULL;

	switch (code) {
	case G_DHCPV6_DNS_SERVERS:
	case G_DHCPV6_SNTP_SERVERS:
		if (len % 16) {
			debug(dhcp_client,
				"%s server list length (%d) is invalid",
				code == G_DHCPV6_DNS_SERVERS ? "DNS" : "SNTP",
				len);
			return NULL;
		}
		for (i = 0; i < len; i += 16) {

			str = g_try_malloc0(INET6_ADDRSTRLEN+1);
			if (!str)
				return list;

			if (!inet_ntop(AF_INET6, &value[i], str,
					INET6_ADDRSTRLEN))
				g_free(str);
			else
				list = g_list_append(list, str);
		}
		break;

	case G_DHCPV6_IA_NA:
	case G_DHCPV6_IA_TA:
	case G_DHCPV6_IA_PD:
		list = get_addresses(dhcp_client, code, len, value, status);
		break;

	case G_DHCPV6_DOMAIN_LIST:
		list = get_domains(len, value);
		break;

	default:
		break;
	}

	return list;
}

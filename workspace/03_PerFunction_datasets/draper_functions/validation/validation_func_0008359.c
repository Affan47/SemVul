mac_in_list(unsigned char *list, int list_len,
			      unsigned char *mac)
{
	while (list_len) {
		if (!memcmp(list, mac, ETH_ALEN))
			return 1;
		list += ETH_ALEN;
		list_len--;
	}
	return 0;
}

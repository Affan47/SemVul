add_conf_by_address(const char *address, int type, const char *username, struct ConfItem *aconf)
{
	static uint32_t prec_value = 0xFFFFFFFF;
	int masktype, bits;
	uint32_t hv;
	struct AddressRec *arec;

	if(address == NULL)
		address = "/NOMATCH!/";
	arec = rb_malloc(sizeof(struct AddressRec));
	masktype = parse_netmask(address, (struct sockaddr *)&arec->Mask.ipa.addr, &bits);
	arec->Mask.ipa.bits = bits;
	arec->masktype = masktype;
#ifdef RB_IPV6
	if(masktype == HM_IPV6)
	{

		bits -= bits % 16;
		arec->next =
			atable[(hv = hash_ipv6((struct sockaddr *)&arec->Mask.ipa.addr, bits))];
		atable[hv] = arec;
	}
	else
#endif
	if(masktype == HM_IPV4)
	{

		bits -= bits % 8;
		arec->next =
			atable[(hv = hash_ipv4((struct sockaddr *)&arec->Mask.ipa.addr, bits))];
		atable[hv] = arec;
	}
	else
	{
		arec->Mask.hostname = address;
		arec->next = atable[(hv = get_mask_hash(address))];
		atable[hv] = arec;
	}
	arec->username = username;
	arec->aconf = aconf;
	arec->type = type;


	if(type == CONF_CLIENT)
		arec->precedence = prec_value--;

	if(EmptyString(username) || (username[0] == '*' && username[1] == '\0'))
		arec->type |= CONF_SKIPUSER;
}

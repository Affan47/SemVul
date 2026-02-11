ipmi_oem_active(struct ipmi_intf * intf, const char * oemtype)
{
	if (intf->oem == NULL)
		return 0;

	if (strncmp(intf->oem->name, oemtype, strlen(oemtype)) == 0)
		return 1;

	return 0;
}

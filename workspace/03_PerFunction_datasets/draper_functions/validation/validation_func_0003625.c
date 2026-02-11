intf_get(intf_t *intf, struct intf_entry *entry)
{
	if (_intf_get_noalias(intf, entry) < 0)
		return (-1);
#ifndef SIOCLIFADDR
	intf->ifc.ifc_buf = (caddr_t)intf->ifcbuf;
	intf->ifc.ifc_len = sizeof(intf->ifcbuf);

	if (ioctl(intf->fd, SIOCGIFCONF, &intf->ifc) < 0)
		return (-1);
#endif
	return (_intf_get_aliases(intf, entry));
}

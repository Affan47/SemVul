hci_get_route(bdaddr_t *bdaddr)
{
	return hci_for_each_dev(HCI_UP, __other_bdaddr,
				(long) (bdaddr ? bdaddr : BDADDR_ANY));
}

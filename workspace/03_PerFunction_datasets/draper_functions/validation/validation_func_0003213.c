request_authentication(int index, bdaddr_t *bdaddr)
{
	struct dev_info *dev = &devs[index];
	auth_requested_cp cp;
	uint16_t handle;
	int err;

	DBG("hci%d", index);

	err = get_handle(index, bdaddr, &handle);
	if (err < 0)
		return err;

	memset(&cp, 0, sizeof(cp));
	cp.handle = htobs(handle);

	if (hci_send_cmd(dev->sk, OGF_LINK_CTL, OCF_AUTH_REQUESTED,
					AUTH_REQUESTED_CP_SIZE, &cp) < 0)
		return -errno;

	return 0;
}

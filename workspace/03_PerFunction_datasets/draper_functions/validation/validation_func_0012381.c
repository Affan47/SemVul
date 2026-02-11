vnic_dev_add_addr(struct vnic_dev *vdev, const u8 *addr)
{
	u64 a0 = 0, a1 = 0;
	int wait = 1000;
	int err;
	int i;

	for (i = 0; i < ETH_ALEN; i++)
		((u8 *)&a0)[i] = addr[i];

	err = vnic_dev_cmd(vdev, CMD_ADDR_ADD, &a0, &a1, wait);
	if (err)
		vdev_neterr("Can't add addr [%pM], %d\n", addr, err);

	return err;
}

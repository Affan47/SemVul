static int instantiate_veth(char *veth1, char *veth2)
{
	int ret;

	ret = lxc_veth_create(veth1, veth2);
	if (ret < 0) {
		usernic_error("Failed to create %s-%s : %s.\n", veth1, veth2,
			      strerror(-ret));
		return -1;
	}


	ret = setup_private_host_hw_addr(veth1);
	if (ret < 0)
		usernic_error("Failed to change mac address of host interface "
			      "%s : %s\n", veth1, strerror(-ret));

	return netdev_set_flag(veth1, IFF_UP);
}

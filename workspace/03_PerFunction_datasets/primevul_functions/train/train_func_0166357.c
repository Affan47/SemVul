static int ipv6_generate_eui64(u8 *eui, struct net_device *dev)
{
	switch (dev->type) {
	case ARPHRD_ETHER:
	case ARPHRD_FDDI:
	case ARPHRD_IEEE802_TR:
		if (dev->addr_len != ETH_ALEN)
			return -1;
		memcpy(eui, dev->dev_addr, 3);
		memcpy(eui + 5, dev->dev_addr + 3, 3);


		if (dev->dev_id) {
			eui[3] = (dev->dev_id >> 8) & 0xFF;
			eui[4] = dev->dev_id & 0xFF;
		} else {
			eui[3] = 0xFF;
			eui[4] = 0xFE;
			eui[0] ^= 2;
		}
		return 0;
	case ARPHRD_ARCNET:

		if (dev->addr_len != ARCNET_ALEN)
			return -1;
		memset(eui, 0, 7);
		eui[7] = *(u8*)dev->dev_addr;
		return 0;
	case ARPHRD_INFINIBAND:
		if (dev->addr_len != INFINIBAND_ALEN)
			return -1;
		memcpy(eui, dev->dev_addr + 12, 8);
		eui[0] |= 2;
		return 0;
	}
	return -1;
}

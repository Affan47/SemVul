iface_get_offload(pcap_t *handle)
{
	int ret;

#ifdef ETHTOOL_GTSO
	ret = iface_ethtool_ioctl(handle, ETHTOOL_GTSO, "ETHTOOL_GTSO");
	if (ret == -1)
		return -1;
	if (ret)
		return 1;
#endif

#ifdef ETHTOOL_GUFO
	ret = iface_ethtool_ioctl(handle, ETHTOOL_GUFO, "ETHTOOL_GUFO");
	if (ret == -1)
		return -1;
	if (ret)
		return 1;
#endif

#ifdef ETHTOOL_GGSO


	ret = iface_ethtool_ioctl(handle, ETHTOOL_GGSO, "ETHTOOL_GGSO");
	if (ret == -1)
		return -1;
	if (ret)
		return 1;
#endif

#ifdef ETHTOOL_GFLAGS
	ret = iface_ethtool_ioctl(handle, ETHTOOL_GFLAGS, "ETHTOOL_GFLAGS");
	if (ret == -1)
		return -1;
	if (ret & ETH_FLAG_LRO)
		return 1;
#endif

#ifdef ETHTOOL_GGRO


	ret = iface_ethtool_ioctl(handle, ETHTOOL_GGRO, "ETHTOOL_GGRO");
	if (ret == -1)
		return -1;
	if (ret)
		return 1;
#endif

	return 0;
}

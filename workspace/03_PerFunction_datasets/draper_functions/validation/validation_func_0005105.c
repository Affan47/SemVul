negotiate_nvsp_ver(struct hv_device *device,
			      struct netvsc_device *net_device,
			      struct nvsp_message *init_packet,
			      u32 nvsp_ver)
{
	struct net_device *ndev = hv_get_drvdata(device);
	int ret;

	memset(init_packet, 0, sizeof(struct nvsp_message));
	init_packet->hdr.msg_type = NVSP_MSG_TYPE_INIT;
	init_packet->msg.init_msg.init.min_protocol_ver = nvsp_ver;
	init_packet->msg.init_msg.init.max_protocol_ver = nvsp_ver;


	ret = vmbus_sendpacket(device->channel, init_packet,
			       sizeof(struct nvsp_message),
			       (unsigned long)init_packet,
			       VM_PKT_DATA_INBAND,
			       VMBUS_DATA_PACKET_FLAG_COMPLETION_REQUESTED);

	if (ret != 0)
		return ret;

	wait_for_completion(&net_device->channel_init_wait);

	if (init_packet->msg.init_msg.init_complete.status !=
	    NVSP_STAT_SUCCESS)
		return -EINVAL;

	if (nvsp_ver == NVSP_PROTOCOL_VERSION_1)
		return 0;


	memset(init_packet, 0, sizeof(struct nvsp_message));
	init_packet->hdr.msg_type = NVSP_MSG2_TYPE_SEND_NDIS_CONFIG;
	init_packet->msg.v2_msg.send_ndis_config.mtu = ndev->mtu + ETH_HLEN;
	init_packet->msg.v2_msg.send_ndis_config.capability.ieee8021q = 1;

	if (nvsp_ver >= NVSP_PROTOCOL_VERSION_5) {
		init_packet->msg.v2_msg.send_ndis_config.capability.sriov = 1;


		init_packet->msg.v2_msg.send_ndis_config.capability.teaming = 1;
	}

	ret = vmbus_sendpacket(device->channel, init_packet,
				sizeof(struct nvsp_message),
				(unsigned long)init_packet,
				VM_PKT_DATA_INBAND, 0);

	return ret;
}

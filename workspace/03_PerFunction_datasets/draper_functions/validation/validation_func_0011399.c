netvsc_destroy_buf(struct hv_device *device)
{
	struct nvsp_message *revoke_packet;
	struct net_device *ndev = hv_get_drvdata(device);
	struct netvsc_device *net_device = net_device_to_netvsc_device(ndev);
	int ret;


	if (net_device->recv_section_cnt) {

		revoke_packet = &net_device->revoke_packet;
		memset(revoke_packet, 0, sizeof(struct nvsp_message));

		revoke_packet->hdr.msg_type =
			NVSP_MSG1_TYPE_REVOKE_RECV_BUF;
		revoke_packet->msg.v1_msg.
		revoke_recv_buf.id = NETVSC_RECEIVE_BUFFER_ID;

		ret = vmbus_sendpacket(device->channel,
				       revoke_packet,
				       sizeof(struct nvsp_message),
				       (unsigned long)revoke_packet,
				       VM_PKT_DATA_INBAND, 0);


		if (ret != 0) {
			netdev_err(ndev, "unable to send "
				"revoke receive buffer to netvsp\n");
			return;
		}
	}


	if (net_device->recv_buf_gpadl_handle) {
		ret = vmbus_teardown_gpadl(device->channel,
					   net_device->recv_buf_gpadl_handle);


		if (ret != 0) {
			netdev_err(ndev,
				   "unable to teardown receive buffer's gpadl\n");
			return;
		}
		net_device->recv_buf_gpadl_handle = 0;
	}

	if (net_device->recv_buf) {

		vfree(net_device->recv_buf);
		net_device->recv_buf = NULL;
	}

	if (net_device->recv_section) {
		net_device->recv_section_cnt = 0;
		kfree(net_device->recv_section);
		net_device->recv_section = NULL;
	}


	if (net_device->send_section_size) {

		revoke_packet = &net_device->revoke_packet;
		memset(revoke_packet, 0, sizeof(struct nvsp_message));

		revoke_packet->hdr.msg_type =
			NVSP_MSG1_TYPE_REVOKE_SEND_BUF;
		revoke_packet->msg.v1_msg.revoke_send_buf.id =
			NETVSC_SEND_BUFFER_ID;

		ret = vmbus_sendpacket(device->channel,
				       revoke_packet,
				       sizeof(struct nvsp_message),
				       (unsigned long)revoke_packet,
				       VM_PKT_DATA_INBAND, 0);


		if (ret != 0) {
			netdev_err(ndev, "unable to send "
				   "revoke send buffer to netvsp\n");
			return;
		}
	}

	if (net_device->send_buf_gpadl_handle) {
		ret = vmbus_teardown_gpadl(device->channel,
					   net_device->send_buf_gpadl_handle);


		if (ret != 0) {
			netdev_err(ndev,
				   "unable to teardown send buffer's gpadl\n");
			return;
		}
		net_device->send_buf_gpadl_handle = 0;
	}
	if (net_device->send_buf) {

		vfree(net_device->send_buf);
		net_device->send_buf = NULL;
	}
	kfree(net_device->send_section_map);
}

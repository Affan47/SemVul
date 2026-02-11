recv_handler(struct ib_mad_agent *agent,
			 struct ib_mad_recv_wc *mad_recv_wc)
{
	struct ib_umad_file *file = agent->context;
	struct ib_umad_packet *packet;

	if (mad_recv_wc->wc->status != IB_WC_SUCCESS)
		goto err1;

	packet = kzalloc(sizeof *packet, GFP_KERNEL);
	if (!packet)
		goto err1;

	packet->length = mad_recv_wc->mad_len;
	packet->recv_wc = mad_recv_wc;

	packet->mad.hdr.status	   = 0;
	packet->mad.hdr.length	   = hdr_size(file) + mad_recv_wc->mad_len;
	packet->mad.hdr.qpn	   = cpu_to_be32(mad_recv_wc->wc->src_qp);
	packet->mad.hdr.lid	   = cpu_to_be16(mad_recv_wc->wc->slid);
	packet->mad.hdr.sl	   = mad_recv_wc->wc->sl;
	packet->mad.hdr.path_bits  = mad_recv_wc->wc->dlid_path_bits;
	packet->mad.hdr.pkey_index = mad_recv_wc->wc->pkey_index;
	packet->mad.hdr.grh_present = !!(mad_recv_wc->wc->wc_flags & IB_WC_GRH);
	if (packet->mad.hdr.grh_present) {
		struct ib_ah_attr ah_attr;

		ib_init_ah_from_wc(agent->device, agent->port_num,
				   mad_recv_wc->wc, mad_recv_wc->recv_buf.grh,
				   &ah_attr);

		packet->mad.hdr.gid_index = ah_attr.grh.sgid_index;
		packet->mad.hdr.hop_limit = ah_attr.grh.hop_limit;
		packet->mad.hdr.traffic_class = ah_attr.grh.traffic_class;
		memcpy(packet->mad.hdr.gid, &ah_attr.grh.dgid, 16);
		packet->mad.hdr.flow_label = cpu_to_be32(ah_attr.grh.flow_label);
	}

	if (queue_packet(file, agent, packet))
		goto err2;
	return;

err2:
	kfree(packet);
err1:
	ib_free_recv_mad(mad_recv_wc);
}

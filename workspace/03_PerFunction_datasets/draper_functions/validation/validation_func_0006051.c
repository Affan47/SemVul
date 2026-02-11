cm_event_connect_error(struct nes_cm_event *event)
{
	struct nes_qp *nesqp;
	struct iw_cm_id *cm_id;
	struct iw_cm_event cm_event;

	int ret;

	if (!event->cm_node)
		return;

	cm_id = event->cm_node->cm_id;
	if (!cm_id)
		return;

	nes_debug(NES_DBG_CM, "cm_node=%p, cm_id=%p\n", event->cm_node, cm_id);
	nesqp = cm_id->provider_data;

	if (!nesqp)
		return;


	nesqp->cm_id = NULL;
	cm_id->provider_data = NULL;
	cm_event.event = IW_CM_EVENT_CONNECT_REPLY;
	cm_event.status = -ECONNRESET;
	cm_event.provider_data = cm_id->provider_data;
	cm_event.local_addr = cm_id->local_addr;
	cm_event.remote_addr = cm_id->remote_addr;
	cm_event.private_data = NULL;
	cm_event.private_data_len = 0;

#ifdef CONFIG_INFINIBAND_NES_DEBUG
	{
		struct sockaddr_in *cm_event_laddr = (struct sockaddr_in *)
						     &cm_event.local_addr;
		struct sockaddr_in *cm_event_raddr = (struct sockaddr_in *)
						     &cm_event.remote_addr;
		nes_debug(NES_DBG_CM, "call CM_EVENT REJECTED, local_addr=%08x, remote_addr=%08x\n",
			  cm_event_laddr->sin_addr.s_addr, cm_event_raddr->sin_addr.s_addr);
	}
#endif

	ret = cm_id->event_handler(cm_id, &cm_event);
	nes_debug(NES_DBG_CM, "OFA CM event_handler returned, ret=%d\n", ret);
	if (ret)
		printk(KERN_ERR "%s[%u] OFA CM event_handler returned, "
		       "ret=%d\n", __func__, __LINE__, ret);
	cm_id->rem_ref(cm_id);

	rem_ref_cm_node(event->cm_node->cm_core, event->cm_node);
	return;
}

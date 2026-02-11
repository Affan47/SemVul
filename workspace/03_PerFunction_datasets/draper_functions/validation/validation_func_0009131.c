send_mpa_reject(struct nes_cm_node *cm_node)
{
	struct sk_buff *skb = NULL;
	u8 start_addr = 0;
	u8 *start_ptr = &start_addr;
	u8 **start_buff = &start_ptr;
	u16 buff_len = 0;
	struct ietf_mpa_v1 *mpa_frame;

	skb = dev_alloc_skb(MAX_CM_BUFFER);
	if (!skb) {
		nes_debug(NES_DBG_CM, "Failed to get a Free pkt\n");
		return -ENOMEM;
	}


	cm_build_mpa_frame(cm_node, start_buff, &buff_len, NULL, MPA_KEY_REPLY);
	mpa_frame = (struct ietf_mpa_v1 *)*start_buff;
	mpa_frame->flags |= IETF_MPA_FLAGS_REJECT;
	form_cm_frame(skb, cm_node, NULL, 0, *start_buff, buff_len, SET_ACK | SET_FIN);

	cm_node->state = NES_CM_STATE_FIN_WAIT1;
	return schedule_nes_timer(cm_node, skb, NES_TIMER_TYPE_SEND, 1, 0);
}

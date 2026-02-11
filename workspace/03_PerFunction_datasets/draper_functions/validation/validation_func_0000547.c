socket_check_flow_control(struct IPC_CHANNEL* ch,
			  int orig_qlen,
			  int curr_qlen)
{
	if (!IPC_ISRCONN(ch)) {
		return;
	}

	if (curr_qlen >= ch->high_flow_mark
	    && ch->high_flow_callback) {
			ch->high_flow_callback(ch, ch->high_flow_userdata);
	}

	if (curr_qlen <= ch->low_flow_mark
	    && orig_qlen > ch->low_flow_mark
	    && ch->low_flow_callback) {
		ch->low_flow_callback(ch, ch->low_flow_userdata);
	}
}

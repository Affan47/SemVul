buildin_kickwaitingroom(struct script_state *st)
{
	struct map_session_data *sd;

	sd = map_id2sd(conv_num(st,& (st->stack->stack_data[st->start+2])));

	if(sd && sd->chatID)
		chat_leavechat(sd,1);
	return 0;
}

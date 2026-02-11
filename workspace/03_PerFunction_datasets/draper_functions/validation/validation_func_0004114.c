buildin_getguildmasterid(struct script_state *st)
{
	int guild_id = conv_num(st,& (st->stack->stack_data[st->start+2]));

	if(guild_id > 0) {
		struct guild *g = guild_search(guild_id);
		if(g) {
			struct map_session_data *sd = map_nick2sd(g->master);
			if(sd) {
				push_val(st->stack,C_INT,sd->status.char_id);
				return 0;
			}
		}
	}
	push_val(st->stack,C_INT,0);
	return 0;
}

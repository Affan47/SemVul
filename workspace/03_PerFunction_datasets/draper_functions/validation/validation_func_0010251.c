transfer_call_step1(struct unistimsession *pte)
{
	struct unistim_subchannel *sub ;
	struct unistim_device *d = pte->device;

	sub = get_sub(d, SUB_REAL);


	if (!sub || !sub->owner) {
		ast_log(LOG_WARNING, "Unable to find subchannel for music on hold\n");
		return;
	}

	if (sub->moh) {
		ast_log(LOG_WARNING, "Transfer with peer already listening music on hold\n");
	} else {
		if (ast_bridged_channel(sub->owner)) {
			ast_moh_start(ast_bridged_channel(sub->owner),
						  sub->parent->musicclass, NULL);
			sub->moh = 1;
			sub->subtype = SUB_THREEWAY;
		} else {
			ast_log(LOG_WARNING, "Unable to find peer subchannel for music on hold\n");
			return;
		}
	}
	sub_start_silence(pte, sub);
	handle_dial_page(pte);
}

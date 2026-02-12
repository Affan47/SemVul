static void *prb_dispatch_next_block(struct kbdq_core *pkc,
		struct packet_sock *po)
{
	struct block_desc *pbd;

	smp_rmb();


	pbd = GET_CURR_PBLOCK_DESC_FROM_CORE(pkc);


	if (TP_STATUS_USER & BLOCK_STATUS(pbd)) {
		prb_freeze_queue(pkc, po);
		return NULL;
	}


	prb_open_block(pkc, pbd);
	return (void *)pkc->nxt_offset;
}

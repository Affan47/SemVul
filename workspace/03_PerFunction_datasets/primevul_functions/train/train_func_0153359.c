static void prb_retire_current_block(struct kbdq_core *pkc,
		struct packet_sock *po, unsigned int status)
{
	struct block_desc *pbd = GET_CURR_PBLOCK_DESC_FROM_CORE(pkc);


	if (likely(TP_STATUS_KERNEL == BLOCK_STATUS(pbd))) {


		if (!(status & TP_STATUS_BLK_TMO)) {
			while (atomic_read(&pkc->blk_fill_in_prog)) {

				cpu_relax();
			}
		}
		prb_close_block(pkc, pbd, po, status);
		return;
	}

	WARN(1, "ERROR-pbd[%d]:%p\n", pkc->kactive_blk_num, pbd);
	dump_stack();
	BUG();
}

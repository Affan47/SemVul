copy_ddcb_results(struct ddcb_requ *req, int ddcb_no)
{
	struct ddcb_queue *queue = req->queue;
	struct ddcb *pddcb = &queue->ddcb_vaddr[req->num];

	memcpy(&req->cmd.asv[0], &pddcb->asv[0], DDCB_ASV_LENGTH);


	req->cmd.vcrc     = be16_to_cpu(pddcb->vcrc_16);
	req->cmd.deque_ts = be64_to_cpu(pddcb->deque_ts_64);
	req->cmd.cmplt_ts = be64_to_cpu(pddcb->cmplt_ts_64);

	req->cmd.attn     = be16_to_cpu(pddcb->attn_16);
	req->cmd.progress = be32_to_cpu(pddcb->progress_32);
	req->cmd.retc     = be16_to_cpu(pddcb->retc_16);

	if (ddcb_requ_collect_debug_data(req)) {
		int prev_no = (ddcb_no == 0) ?
			queue->ddcb_max - 1 : ddcb_no - 1;
		struct ddcb *prev_pddcb = &queue->ddcb_vaddr[prev_no];

		memcpy(&req->debug_data.ddcb_finished, pddcb,
		       sizeof(req->debug_data.ddcb_finished));
		memcpy(&req->debug_data.ddcb_prev, prev_pddcb,
		       sizeof(req->debug_data.ddcb_prev));
	}
}

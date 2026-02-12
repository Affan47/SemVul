ccp_run_rsa_cmd(struct ccp_cmd_queue *cmd_q, struct ccp_cmd *cmd)
{
	struct ccp_rsa_engine *rsa = &cmd->u.rsa;
	struct ccp_dm_workarea exp, src, dst;
	struct ccp_op op;
	unsigned int sb_count, i_len, o_len;
	int ret;


	if (rsa->key_size > cmd_q->ccp->vdata->rsamax)
		return -EINVAL;

	if (!rsa->exp || !rsa->mod || !rsa->src || !rsa->dst)
		return -EINVAL;

	memset(&op, 0, sizeof(op));
	op.cmd_q = cmd_q;
	op.jobid = CCP_NEW_JOBID(cmd_q->ccp);


	o_len = 32 * ((rsa->key_size + 255) / 256);
	i_len = o_len * 2;

	sb_count = 0;
	if (cmd_q->ccp->vdata->version < CCP_VERSION(5, 0)) {


		sb_count = o_len / CCP_SB_BYTES;
		op.sb_key = cmd_q->ccp->vdata->perform->sballoc(cmd_q,
								sb_count);
		if (!op.sb_key)
			return -EIO;
	} else {


		op.sb_key = cmd_q->sb_key;
	}


	ret = ccp_init_dm_workarea(&exp, cmd_q, o_len, DMA_TO_DEVICE);
	if (ret)
		goto e_sb;

	ret = ccp_reverse_set_dm_area(&exp, 0, rsa->exp, 0, rsa->exp_len);
	if (ret)
		goto e_exp;

	if (cmd_q->ccp->vdata->version < CCP_VERSION(5, 0)) {


		ret = ccp_copy_to_sb(cmd_q, &exp, op.jobid, op.sb_key,
				     CCP_PASSTHRU_BYTESWAP_NOOP);
		if (ret) {
			cmd->engine_error = cmd_q->cmd_error;
			goto e_exp;
		}
	} else {

		op.exp.u.dma.address = exp.dma.address;
		op.exp.u.dma.offset = 0;
	}


	ret = ccp_init_dm_workarea(&src, cmd_q, i_len, DMA_TO_DEVICE);
	if (ret)
		goto e_exp;

	ret = ccp_reverse_set_dm_area(&src, 0, rsa->mod, 0, rsa->mod_len);
	if (ret)
		goto e_src;
	ret = ccp_reverse_set_dm_area(&src, o_len, rsa->src, 0, rsa->src_len);
	if (ret)
		goto e_src;


	ret = ccp_init_dm_workarea(&dst, cmd_q, o_len, DMA_FROM_DEVICE);
	if (ret)
		goto e_src;

	op.soc = 1;
	op.src.u.dma.address = src.dma.address;
	op.src.u.dma.offset = 0;
	op.src.u.dma.length = i_len;
	op.dst.u.dma.address = dst.dma.address;
	op.dst.u.dma.offset = 0;
	op.dst.u.dma.length = o_len;

	op.u.rsa.mod_size = rsa->key_size;
	op.u.rsa.input_len = i_len;

	ret = cmd_q->ccp->vdata->perform->rsa(&op);
	if (ret) {
		cmd->engine_error = cmd_q->cmd_error;
		goto e_dst;
	}

	ccp_reverse_get_dm_area(&dst, 0, rsa->dst, 0, rsa->mod_len);

e_dst:
	ccp_dm_free(&dst);

e_src:
	ccp_dm_free(&src);

e_exp:
	ccp_dm_free(&exp);

e_sb:
	if (sb_count)
		cmd_q->ccp->vdata->perform->sbfree(cmd_q, op.sb_key, sb_count);

	return ret;
}

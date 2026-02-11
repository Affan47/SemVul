sst_drain_stream(struct intel_sst_drv *sst_drv_ctx,
			int str_id, bool partial_drain)
{
	int retval = 0;
	struct stream_info *str_info;

	dev_dbg(sst_drv_ctx->dev, "SST DBG:sst_drain_stream for %d\n", str_id);
	str_info = get_stream_info(sst_drv_ctx, str_id);
	if (!str_info)
		return -EINVAL;
	if (str_info->status != STREAM_RUNNING &&
		str_info->status != STREAM_INIT &&
		str_info->status != STREAM_PAUSED) {
			dev_err(sst_drv_ctx->dev, "SST ERR: BADQRC for stream = %d\n",
				       str_info->status);
			return -EBADRQC;
	}

	retval = sst_prepare_and_post_msg(sst_drv_ctx, str_info->task_id, IPC_CMD,
			IPC_IA_DRAIN_STREAM_MRFLD, str_info->pipe_id,
			sizeof(u8), &partial_drain, NULL, true, true, false, false);


	return retval;
}

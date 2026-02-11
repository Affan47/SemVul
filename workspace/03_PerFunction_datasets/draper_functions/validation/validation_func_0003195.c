sst_cdev_set_metadata(struct device *dev,
		unsigned int str_id, struct snd_compr_metadata *metadata)
{
	int retval = 0;
	struct stream_info *str_info;
	struct intel_sst_drv *ctx = dev_get_drvdata(dev);

	dev_dbg(dev, "set metadata for stream %d\n", str_id);

	str_info = get_stream_info(ctx, str_id);
	if (!str_info)
		return -EINVAL;

	dev_dbg(dev, "pipe id = %d\n", str_info->pipe_id);
	retval = sst_prepare_and_post_msg(ctx, str_info->task_id, IPC_CMD,
			IPC_IA_SET_STREAM_PARAMS_MRFLD, str_info->pipe_id,
			sizeof(*metadata), metadata, NULL,
			true, true, true, false);

	return retval;
}

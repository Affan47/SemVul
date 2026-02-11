skl_ipc_delete_pipeline(struct sst_generic_ipc *ipc, u8 instance_id)
{
	struct skl_ipc_header header = {0};
	u64 *ipc_header = (u64 *)(&header);
	int ret;

	header.primary = IPC_MSG_TARGET(IPC_FW_GEN_MSG);
	header.primary |= IPC_MSG_DIR(IPC_MSG_REQUEST);
	header.primary |= IPC_GLB_TYPE(IPC_GLB_DELETE_PPL);
	header.primary |= IPC_INSTANCE_ID(instance_id);

	dev_dbg(ipc->dev, "In %s header=%d\n", __func__, header.primary);
	ret = sst_ipc_tx_message_wait(ipc, *ipc_header, NULL, 0, NULL, 0);
	if (ret < 0) {
		dev_err(ipc->dev, "ipc: delete pipeline failed, err %d\n", ret);
		return ret;
	}

	return 0;
}

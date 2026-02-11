be_cmd_pmac_del(struct be_adapter *adapter, u32 if_id, int pmac_id, u32 dom)
{
	struct be_mcc_wrb *wrb;
	struct be_cmd_req_pmac_del *req;
	int status;

	if (pmac_id == -1)
		return 0;

	spin_lock_bh(&adapter->mcc_lock);

	wrb = wrb_from_mccq(adapter);
	if (!wrb) {
		status = -EBUSY;
		goto err;
	}
	req = embedded_payload(wrb);

	be_wrb_cmd_hdr_prepare(&req->hdr, CMD_SUBSYSTEM_COMMON,
			       OPCODE_COMMON_NTWK_PMAC_DEL, sizeof(*req),
			       wrb, NULL);

	req->hdr.domain = dom;
	req->if_id = cpu_to_le32(if_id);
	req->pmac_id = cpu_to_le32(pmac_id);

	status = be_mcc_notify_wait(adapter);

err:
	spin_unlock_bh(&adapter->mcc_lock);
	return status;
}

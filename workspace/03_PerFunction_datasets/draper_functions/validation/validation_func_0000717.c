HpmfwupgAbortUpgrade(struct ipmi_intf *intf,
		struct HpmfwupgAbortUpgradeCtx *pCtx)
{
	int rc = HPMFWUPG_SUCCESS;
	struct ipmi_rs *rsp;
	struct ipmi_rq req;
	pCtx->req.picmgId = HPMFWUPG_PICMG_IDENTIFIER;
	memset(&req, 0, sizeof(req));
	req.msg.netfn = IPMI_NETFN_PICMG;
	req.msg.cmd = HPMFWUPG_ABORT_UPGRADE;
	req.msg.data = (unsigned char*)&pCtx->req;
	req.msg.data_len = sizeof(struct HpmfwupgAbortUpgradeReq);
	rsp = HpmfwupgSendCmd(intf, req, NULL);
	if (rsp == NULL) {
		lprintf(LOG_ERR, "Error - aborting upgrade.");
		return HPMFWUPG_ERROR;
	}
	if (rsp->ccode != 0x00) {
		lprintf(LOG_ERR, "Error aborting upgrade");
		lprintf(LOG_ERR, "compcode=0x%x: %s",
				rsp->ccode,
				val2str(rsp->ccode, completion_code_vals));
		rc = HPMFWUPG_ERROR;
	}
	return rc;
}

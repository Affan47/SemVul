nvme_fill_device_id_scsi_string(struct nvme_ns *ns,
		struct sg_io_hdr *hdr, u8 *inq_response, int alloc_len)
{
	struct nvme_ctrl *ctrl = ns->ctrl;
	struct nvme_id_ctrl *id_ctrl;
	int nvme_sc, res;

	if (alloc_len < 72) {
		return nvme_trans_completion(hdr,
				SAM_STAT_CHECK_CONDITION,
				ILLEGAL_REQUEST, SCSI_ASC_INVALID_CDB,
				SCSI_ASCQ_CAUSE_NOT_REPORTABLE);
	}

	nvme_sc = nvme_identify_ctrl(ctrl, &id_ctrl);
	res = nvme_trans_status_code(hdr, nvme_sc);
	if (res)
		return res;

	memset(inq_response, 0, alloc_len);
	inq_response[1] = INQ_DEVICE_IDENTIFICATION_PAGE;
	inq_response[3] = 0x48;


	inq_response[4] = 0x03;
	inq_response[5] = 0x08;
	inq_response[6] = 0x00;
	inq_response[7] = 0x44;

	sprintf(&inq_response[8], "%04x", le16_to_cpu(id_ctrl->vid));
	memcpy(&inq_response[12], ctrl->model, sizeof(ctrl->model));
	sprintf(&inq_response[52], "%04x", cpu_to_be32(ns->ns_id));
	memcpy(&inq_response[56], ctrl->serial, sizeof(ctrl->serial));

	res = nvme_trans_copy_to_user(hdr, inq_response, alloc_len);
	kfree(id_ctrl);
	return res;
}

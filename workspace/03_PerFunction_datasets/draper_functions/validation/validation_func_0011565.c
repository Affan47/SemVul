qla2x00_gff_id(scsi_qla_host_t *vha, sw_info_t *list)
{
	int		rval;
	uint16_t	i;

	ms_iocb_entry_t	*ms_pkt;
	struct ct_sns_req	*ct_req;
	struct ct_sns_rsp	*ct_rsp;
	struct qla_hw_data *ha = vha->hw;
	uint8_t fcp_scsi_features = 0;

	for (i = 0; i < ha->max_fibre_devices; i++) {


		list[i].fc4_type = FC4_TYPE_UNKNOWN;


		if (!IS_FWI2_CAPABLE(ha))
			continue;


		ms_pkt = ha->isp_ops->prep_ms_iocb(vha, GFF_ID_REQ_SIZE,
		    GFF_ID_RSP_SIZE);


		ct_req = qla2x00_prep_ct_req(ha->ct_sns, GFF_ID_CMD,
		    GFF_ID_RSP_SIZE);
		ct_rsp = &ha->ct_sns->p.rsp;


		ct_req->req.port_id.port_id[0] = list[i].d_id.b.domain;
		ct_req->req.port_id.port_id[1] = list[i].d_id.b.area;
		ct_req->req.port_id.port_id[2] = list[i].d_id.b.al_pa;


		rval = qla2x00_issue_iocb(vha, ha->ms_iocb, ha->ms_iocb_dma,
		   sizeof(ms_iocb_entry_t));

		if (rval != QLA_SUCCESS) {
			ql_dbg(ql_dbg_disc, vha, 0x205c,
			    "GFF_ID issue IOCB failed (%d).\n", rval);
		} else if (qla2x00_chk_ms_status(vha, ms_pkt, ct_rsp,
			       "GFF_ID") != QLA_SUCCESS) {
			ql_dbg(ql_dbg_disc, vha, 0x205d,
			    "GFF_ID IOCB status had a failure status code.\n");
		} else {
			fcp_scsi_features =
			   ct_rsp->rsp.gff_id.fc4_features[GFF_FCP_SCSI_OFFSET];
			fcp_scsi_features &= 0x0f;

			if (fcp_scsi_features)
				list[i].fc4_type = FC4_TYPE_FCP_SCSI;
			else
				list[i].fc4_type = FC4_TYPE_OTHER;
		}


		if (list[i].d_id.b.rsvd_1 != 0)
			break;
	}
}

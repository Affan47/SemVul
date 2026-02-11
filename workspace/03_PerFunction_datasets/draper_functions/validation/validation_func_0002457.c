qla2x00_get_dcbx_params(scsi_qla_host_t *vha, dma_addr_t tlv_dma,
    uint16_t size)
{
	int rval;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x10f1,
	    "Entered %s.\n", __func__);

	if (!IS_CNA_CAPABLE(vha->hw))
		return QLA_FUNCTION_FAILED;

	mcp->mb[0] = MBC_GET_DCBX_PARAMS;
	mcp->mb[1] = 0;
	mcp->mb[2] = MSW(tlv_dma);
	mcp->mb[3] = LSW(tlv_dma);
	mcp->mb[6] = MSW(MSD(tlv_dma));
	mcp->mb[7] = LSW(MSD(tlv_dma));
	mcp->mb[8] = size;
	mcp->out_mb = MBX_8|MBX_7|MBX_6|MBX_3|MBX_2|MBX_1|MBX_0;
	mcp->in_mb = MBX_2|MBX_1|MBX_0;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;
	rval = qla2x00_mailbox_command(vha, mcp);

	if (rval != QLA_SUCCESS) {
		ql_dbg(ql_dbg_mbx, vha, 0x10f2,
		    "Failed=%x mb[0]=%x mb[1]=%x mb[2]=%x.\n",
		    rval, mcp->mb[0], mcp->mb[1], mcp->mb[2]);
	} else {
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x10f3,
		    "Done %s.\n", __func__);
	}

	return rval;
}

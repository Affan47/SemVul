qla2x00_write_ram_word(scsi_qla_host_t *vha, uint32_t risc_addr, uint32_t data)
{
	int rval;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1100,
	    "Entered %s.\n", __func__);

	if (!IS_FWI2_CAPABLE(vha->hw))
		return QLA_FUNCTION_FAILED;

	mcp->mb[0] = MBC_WRITE_RAM_WORD_EXTENDED;
	mcp->mb[1] = LSW(risc_addr);
	mcp->mb[2] = LSW(data);
	mcp->mb[3] = MSW(data);
	mcp->mb[8] = MSW(risc_addr);
	mcp->out_mb = MBX_8|MBX_3|MBX_2|MBX_1|MBX_0;
	mcp->in_mb = MBX_0;
	mcp->tov = 30;
	mcp->flags = 0;
	rval = qla2x00_mailbox_command(vha, mcp);
	if (rval != QLA_SUCCESS) {
		ql_dbg(ql_dbg_mbx, vha, 0x1101,
		    "Failed=%x mb[0]=%x.\n", rval, mcp->mb[0]);
	} else {
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1102,
		    "Done %s.\n", __func__);
	}

	return rval;
}

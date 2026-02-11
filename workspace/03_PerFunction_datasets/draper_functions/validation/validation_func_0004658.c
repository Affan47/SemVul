qla2x00_issue_iocb_timeout(scsi_qla_host_t *vha, void *buffer,
    dma_addr_t phys_addr, size_t size, uint32_t tov)
{
	int		rval;
	mbx_cmd_t	mc;
	mbx_cmd_t	*mcp = &mc;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1038,
	    "Entered %s.\n", __func__);

	mcp->mb[0] = MBC_IOCB_COMMAND_A64;
	mcp->mb[1] = 0;
	mcp->mb[2] = MSW(phys_addr);
	mcp->mb[3] = LSW(phys_addr);
	mcp->mb[6] = MSW(MSD(phys_addr));
	mcp->mb[7] = LSW(MSD(phys_addr));
	mcp->out_mb = MBX_7|MBX_6|MBX_3|MBX_2|MBX_1|MBX_0;
	mcp->in_mb = MBX_2|MBX_0;
	mcp->tov = tov;
	mcp->flags = 0;
	rval = qla2x00_mailbox_command(vha, mcp);

	if (rval != QLA_SUCCESS) {

		ql_dbg(ql_dbg_mbx, vha, 0x1039, "Failed=%x.\n", rval);
	} else {
		sts_entry_t *sts_entry = (sts_entry_t *) buffer;


		sts_entry->entry_status &=
		    IS_FWI2_CAPABLE(vha->hw) ? RF_MASK_24XX : RF_MASK;
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x103a,
		    "Done %s.\n", __func__);
	}

	return rval;
}

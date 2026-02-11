qlafx00_mbx_completion(scsi_qla_host_t *vha, uint32_t mb0)
{
	uint16_t	cnt;
	uint32_t __iomem *wptr;
	struct qla_hw_data *ha = vha->hw;
	struct device_reg_fx00 __iomem *reg = &ha->iobase->ispfx00;

	if (!ha->mcp32)
		ql_dbg(ql_dbg_async, vha, 0x507e, "MBX pointer ERROR.\n");


	ha->flags.mbox_int = 1;
	ha->mailbox_out32[0] = mb0;
	wptr = (uint32_t __iomem *)&reg->mailbox17;

	for (cnt = 1; cnt < ha->mbx_count; cnt++) {
		ha->mailbox_out32[cnt] = RD_REG_DWORD(wptr);
		wptr++;
	}
}

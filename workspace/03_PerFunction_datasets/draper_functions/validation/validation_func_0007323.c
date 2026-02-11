qla8044_minidump_process_rdmux2(struct scsi_qla_host *vha,
	struct qla8044_minidump_entry_hdr *entry_hdr, uint32_t **d_ptr)
{
	uint32_t sel_val1, sel_val2, t_sel_val, data, i;
	uint32_t sel_addr1, sel_addr2, sel_val_mask, read_addr;
	struct qla8044_minidump_entry_rdmux2 *rdmux2_hdr;
	uint32_t *data_ptr = *d_ptr;

	rdmux2_hdr = (struct qla8044_minidump_entry_rdmux2 *) entry_hdr;
	sel_val1 = rdmux2_hdr->select_value_1;
	sel_val2 = rdmux2_hdr->select_value_2;
	sel_addr1 = rdmux2_hdr->select_addr_1;
	sel_addr2 = rdmux2_hdr->select_addr_2;
	sel_val_mask = rdmux2_hdr->select_value_mask;
	read_addr = rdmux2_hdr->read_addr;

	for (i = 0; i < rdmux2_hdr->op_count; i++) {
		qla8044_wr_reg_indirect(vha, sel_addr1, sel_val1);
		t_sel_val = sel_val1 & sel_val_mask;
		*data_ptr++ = t_sel_val;

		qla8044_wr_reg_indirect(vha, sel_addr2, t_sel_val);
		qla8044_rd_reg_indirect(vha, read_addr, &data);

		*data_ptr++ = data;

		qla8044_wr_reg_indirect(vha, sel_addr1, sel_val2);
		t_sel_val = sel_val2 & sel_val_mask;
		*data_ptr++ = t_sel_val;

		qla8044_wr_reg_indirect(vha, sel_addr2, t_sel_val);
		qla8044_rd_reg_indirect(vha, read_addr, &data);

		*data_ptr++ = data;

		sel_val1 += rdmux2_hdr->select_value_stride;
		sel_val2 += rdmux2_hdr->select_value_stride;
	}

	*d_ptr = data_ptr;
}

presub_helper(
	struct radeon_compiler * c,
	struct rc_instruction * inst_add,
	rc_presubtract_op presub_opcode,
	rc_presub_replace_fn presub_replace)
{
	struct rc_reader_data reader_data;
	unsigned int i;
	rc_presubtract_op cb_op = presub_opcode;

	reader_data.CbData = &cb_op;
	reader_data.ExitOnAbort = 1;
	rc_get_readers(c, inst_add, &reader_data, presub_scan_read, NULL,
						is_src_clobbered_scan_write);

	if (reader_data.Abort || reader_data.ReaderCount == 0)
		return 0;

	for(i = 0; i < reader_data.ReaderCount; i++) {
		unsigned int src_index;
		struct rc_reader reader = reader_data.Readers[i];
		const struct rc_opcode_info * info =
				rc_get_opcode_info(reader.Inst->U.I.Opcode);

		for (src_index = 0; src_index < info->NumSrcRegs; src_index++) {
			if (&reader.Inst->U.I.SrcReg[src_index] == reader.U.I.Src)
				presub_replace(inst_add, reader.Inst, src_index);
		}
	}
	return 1;
}

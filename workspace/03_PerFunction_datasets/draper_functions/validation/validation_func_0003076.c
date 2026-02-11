allocate_and_insert_proxies(struct emulate_branch_state * s,
		struct register_proxies * proxies,
		struct rc_instruction * begin,
		struct rc_instruction * end)
{
	struct state_and_proxies sap;

	sap.S = s;
	sap.Proxies = proxies;

	for(struct rc_instruction * inst = begin; inst != end; inst = inst->Next) {
		rc_for_all_writes_mask(inst, scan_write, &sap);
		rc_remap_registers(inst, remap_proxy_function, &sap);
	}

	for(unsigned int index = 0; index < RC_REGISTER_MAX_INDEX; ++index) {
		if (proxies->Temporary[index].Proxied) {
			struct rc_instruction * inst_mov = rc_insert_new_instruction(s->C, begin->Prev);
			inst_mov->U.I.Opcode = RC_OPCODE_MOV;
			inst_mov->U.I.DstReg.File = RC_FILE_TEMPORARY;
			inst_mov->U.I.DstReg.Index = proxies->Temporary[index].Index;
			inst_mov->U.I.DstReg.WriteMask = RC_MASK_XYZW;
			inst_mov->U.I.SrcReg[0].File = RC_FILE_TEMPORARY;
			inst_mov->U.I.SrcReg[0].Index = index;
		}
	}
}

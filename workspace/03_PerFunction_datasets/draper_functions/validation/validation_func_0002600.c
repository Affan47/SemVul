rc_transform_fragment_face(struct radeon_compiler *c, unsigned face)
{
	unsigned tempregi = rc_find_free_temporary(c);
	struct rc_instruction *inst_add;
	struct rc_instruction *inst;


	inst_add = rc_insert_new_instruction(c, &c->Program.Instructions);
	inst_add->U.I.Opcode = RC_OPCODE_ADD;

	inst_add->U.I.DstReg.File = RC_FILE_TEMPORARY;
	inst_add->U.I.DstReg.Index = tempregi;
	inst_add->U.I.DstReg.WriteMask = RC_MASK_X;

	inst_add->U.I.SrcReg[0].File = RC_FILE_NONE;
	inst_add->U.I.SrcReg[0].Swizzle = RC_SWIZZLE_1111;

	inst_add->U.I.SrcReg[1].File = RC_FILE_INPUT;
	inst_add->U.I.SrcReg[1].Index = face;
	inst_add->U.I.SrcReg[1].Swizzle = RC_SWIZZLE_XXXX;
	inst_add->U.I.SrcReg[1].Negate = RC_MASK_XYZW;

	for (inst = inst_add->Next; inst != &c->Program.Instructions; inst = inst->Next) {
		const struct rc_opcode_info * opcode = rc_get_opcode_info(inst->U.I.Opcode);
		unsigned i;

		for(i = 0; i < opcode->NumSrcRegs; i++) {
			if (inst->U.I.SrcReg[i].File == RC_FILE_INPUT &&
			    inst->U.I.SrcReg[i].Index == face) {
				inst->U.I.SrcReg[i].File = RC_FILE_TEMPORARY;
				inst->U.I.SrcReg[i].Index = tempregi;
			}
		}
	}
}

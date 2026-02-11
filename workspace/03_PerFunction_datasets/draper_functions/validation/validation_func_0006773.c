step_jump(struct sim_device *dev, uint16_t ins)
{
	uint16_t opcode = ins & 0xfc00;
	uint16_t pc_offset = (ins & 0x03ff) << 1;
	uint16_t sr = dev->regs[MSP430_REG_SR];

	if (pc_offset & 0x0400)
		pc_offset |= 0xff800;

	switch (opcode) {
	case MSP430_OP_JNZ:
		sr = !(sr & MSP430_SR_Z);
		break;

	case MSP430_OP_JZ:
		sr &= MSP430_SR_Z;
		break;

	case MSP430_OP_JNC:
		sr = !(sr & MSP430_SR_C);
		break;

	case MSP430_OP_JC:
		sr &= MSP430_SR_C;
		break;

	case MSP430_OP_JN:
		sr &= MSP430_SR_N;
		break;

	case MSP430_OP_JGE:
		sr = ((sr & MSP430_SR_N) ? 1 : 0) ==
			((sr & MSP430_SR_V) ? 1 : 0);
		break;

	case MSP430_OP_JL:
		sr = ((sr & MSP430_SR_N) ? 1 : 0) !=
			((sr & MSP430_SR_V) ? 1 : 0);
		break;

	case MSP430_OP_JMP:
		sr = 1;
		break;
	}

	if (sr)
		dev->regs[MSP430_REG_PC] += pc_offset;

	return 0;
}

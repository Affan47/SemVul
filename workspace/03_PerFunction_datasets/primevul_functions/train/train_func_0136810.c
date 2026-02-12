_lou_findOpcodeName(TranslationTableOpcode opcode) {
	static char scratchBuf[MAXSTRING];

	if (opcode < 0 || opcode >= CTO_None) {
		sprintf(scratchBuf, "%u", opcode);
		return scratchBuf;
	}
	return opcodeNames[opcode];
}

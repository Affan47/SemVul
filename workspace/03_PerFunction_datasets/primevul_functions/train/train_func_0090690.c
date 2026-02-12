static ut32 decodeBitMasks(ut32 imm) {

	int size = 32;

	ut32 cto, i;
	ut32 mask = ((ut64) - 1LL) >> (64 - size);

	if (isShiftedMask (imm)) {
		i = countTrailingZeros (imm);
		cto = countTrailingOnes (imm >> i);
	} else {
		imm |= ~mask;
		if (!isShiftedMask (imm)) {
			return UT32_MAX;
		}

		ut32 clo = countLeadingOnes (imm);
		i = 64 - clo;
		cto = clo + countTrailingOnes (imm) - (64 - size);
	}


	ut32 immr = (size - i) & (size - 1);


	ut64 nimms = ~(size - 1) << 1;


	nimms |= (cto - 1);

	ut32 n = ((nimms >> 6) & 1) ^ 1;
	ut64 encoding = (n << 12) | (immr << 6) | (nimms & 0x3f);
	return encoding;
}

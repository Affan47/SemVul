passGetNumber(CharsString *passLine, int *passLinepos, widechar *passHoldNumber) {

	*passHoldNumber = 0;
	while ((*passLinepos < passLine->length) && (passLine->chars[*passLinepos] >= '0') &&
			(passLine->chars[*passLinepos] <= '9'))
		*passHoldNumber =
				10 * (*passHoldNumber) + (passLine->chars[(*passLinepos)++] - '0');
	return 1;
}

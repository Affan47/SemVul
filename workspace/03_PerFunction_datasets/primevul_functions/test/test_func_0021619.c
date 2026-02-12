passGetNumber(CharsString *passLine, int *passLinepos, widechar *number) {

	*number = 0;
	while ((*passLinepos < passLine->length) && (passLine->chars[*passLinepos] >= '0') &&
			(passLine->chars[*passLinepos] <= '9'))
		*number = 10 * (*number) + (passLine->chars[(*passLinepos)++] - '0');
	return 1;
}

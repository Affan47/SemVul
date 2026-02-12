passGetName(CharsString *passLine, int *passLinepos, CharsString *name) {
	name->length = 0;

	do {
		widechar c = passLine->chars[*passLinepos];
		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
			name->chars[name->length++] = c;
			(*passLinepos)++;
		} else {
			break;
		}
	} while (*passLinepos < passLine->length);
	return 1;
}

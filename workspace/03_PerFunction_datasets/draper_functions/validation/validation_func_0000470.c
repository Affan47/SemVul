printActions(byte *p, unsigned long int length, unsigned long int maxActions, char **regtable)
{


	unsigned long int i = 0;
	unsigned long int curAction = 0;
	unsigned int blocklen;

	while ((i < length) && (curAction < maxActions)) {
		Action type = (Action) p[i];

		checkLabel(p + i - buffer);
		swfrelpos = p + i - buffer;

		++i;

		if ((type & 0x80) != 0) {
			blocklen = S16(p + i);
			i += 2;
		}
		else
			blocklen = 0;

		if (i+blocklen <= length)
			printActionRecord(p + i, type, &blocklen, regtable);
		else {
			tellUser(0, "Disassembly may be incomplete: wrong action length encountered");
			return length;
		}

		i += blocklen;
		curAction++;
	}

	checkLabel(p + i - buffer);

	return i;
}

createLabels(unsigned long int length)
{
	unsigned long int i;
	unsigned int blocklen;
	unsigned int numpools = 0;

	numLabels = 0;
	curLabel = 0;
	for (i = 0; i < length; ++i) {
		if (buffer[i] & 0x80) {
			blocklen = S16(buffer + i + 1);

			if ((Action) buffer[i] == SWFACTION_BRANCHALWAYS || (Action) buffer[i] == SWFACTION_BRANCHIFTRUE) {
				if ((signed long int) (i + 3 + blocklen + S16signed(buffer + i + 3)) >= 0) {
					addLabel(i + 3 + blocklen + S16signed(buffer + i + 3));
				}
			}
			else if ((Action) buffer[i] == SWFACTION_CONSTANTPOOL) {
				byte *p = buffer + i + 3;
				unsigned int n, nStrings = S16(p);
				numpools++;
				p += 2;
				for (n = 0; n < nStrings; ++n)
					p += strlen((char *) p) + 1;

				if (blocklen != p - buffer - i - 3) {

					blocklen = p - buffer - i - 3;
				}
			}

			i += blocklen + 2;
		}
	}
	if ((numpools > 1) && (literalconstants < 2))
		showLiterals = 0;
}

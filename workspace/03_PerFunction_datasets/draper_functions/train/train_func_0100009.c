findtoc (struct cdunit *cdu, int *sectorp)
{
	int i;
	int sector;

	if (*sectorp < 0)
		return NULL;
	sector = *sectorp;
	for (i = 0; i <= cdu->tracks; i++) {
		struct cdtoc *t = &cdu->toc[i];
		if (t->address > sector) {
			if (i == 0) {
				*sectorp = 0;
				return t;
			}
			t--;
			sector -= t->address;
			*sectorp = sector;
			return t;
		}
	}
	return NULL;
}

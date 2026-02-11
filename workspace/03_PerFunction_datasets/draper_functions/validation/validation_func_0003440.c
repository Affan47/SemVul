put(const BookEntry & newentry)
{
	unsigned long slot = 0;
	for (unsigned int i=0; i<header.size; i++) {
		slot = hashfunc(newentry.hashkey, i);

		BookEntry oldentry = read_entry(slot);
		if (oldentry.is_empty()) {

#ifdef DEBUG
			if (i > 5) {
				printf("(%d)", i); fflush(stdout);
			}
#endif
			break;
		} else if (oldentry.hashkey != newentry.hashkey) {

			if (i == header.size-1) {
#ifdef DEBUG
				printf("X"); fflush(stdout);
#endif
				return false;
			}
			continue;
		} else {

#ifdef DEBUG
			printf("O"); fflush(stdout);
#endif
			break;
		}

	}

	write_entry(slot, newentry);
	return true;
}

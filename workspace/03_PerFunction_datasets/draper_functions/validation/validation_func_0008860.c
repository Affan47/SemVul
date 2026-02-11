get_unused_blocks(UnusedRange *unused, unsigned *numunusedptr) {
	unsigned &numunused = *numunusedptr;

	unsigned last = 0;
	std::list<Match>::iterator lastnext = unused[0].ml;
	for (unsigned i = 0; i < numunused; ++i) {
		unsigned nextstart = unused[i].p + unused[i].num;

		std::list<Match>::iterator mr = unused[i].ml;
		unused[i] = UnusedRange(last, unused[i].p < last ? 0 : unused[i].p - last, lastnext, mr);
		lastnext = next(mr);

		last = std::max(last, nextstart);
	}
}

tally_new(unsigned buckets)
{
	struct tally *tally;


	if (buckets == 0) {
		buckets = 1;
	}


	if (sizeof(*tally) * buckets / sizeof(*tally) != buckets) {
		return NULL;
	}

	tally = (struct tally *)malloc(
		sizeof(*tally) + sizeof(tally->counts[0])*(buckets-1));
	if (tally == NULL) {
		return NULL;
	}

	tally->max = ((size_t)1 << (SIZET_BITS - 1));
	tally->min = ~tally->max;
	tally->total[0] = tally->total[1] = 0;
	tally->buckets = buckets;
	tally->step_bits = 0;
	memset(tally->counts, 0, sizeof(tally->counts[0])*buckets);
	return tally;
}

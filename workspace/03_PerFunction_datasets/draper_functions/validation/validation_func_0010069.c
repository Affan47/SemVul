MeanReductionPop(WiggleIterator * wi) {
	int i;

	if (wi->done)
		return;

	WiggleReducerData * data = (WiggleReducerData *) wi->data;
	Multiplexer * multi = data->multi;

	if (multi->done) {
		wi->done = true;
		return;
	}

	wi->chrom = multi->chrom;
	wi->start = multi->start;
	wi->finish = multi->finish;
	wi->value = 0;
	for (i = 0; i < multi->count; i++) {
		double value;
		if (multi->inplay[i])
			value = multi->values[i];
		else
			value = multi->default_values[i];

		if (isnan(value)) {
			wi->value = NAN;
			break;
		}

		wi->value += value;
	}
	if (!isnan(wi->value))
		wi->value /= multi->count;
	popMultiplexer(multi);
}

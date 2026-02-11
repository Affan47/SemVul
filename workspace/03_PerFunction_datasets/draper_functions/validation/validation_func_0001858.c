VarianceReduction(Multiplexer * multi) {
	WiggleReducerData * data = (WiggleReducerData *) calloc(1, sizeof(WiggleReducerData));
	data->multi = multi;
	int i;
	double sum = 0;
	for (i = 0; i < multi->count; i++) {
		if (isnan(data->multi->default_values[i])) {
			sum = NAN;
			break;
		}
		sum += data->multi->default_values[i];
	}
	double default_value;
	if (isnan(sum))
		default_value = NAN;
	else {
		double mean = sum / multi->count;
		double error = 0;
		for (i = 0; i < multi->count; i++)
			error += (data->multi->default_values[i] - mean) * (data->multi->default_values[i] - mean);
		default_value = error/multi->count;
	}

	return newWiggleIterator(data, &VarianceReductionPop, &WiggleReducerSeek, default_value);
}

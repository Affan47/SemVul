hkl_sample_list_get_by_name(HklSampleList *self, char const *name)
{
	HklSample *sample = NULL;
	size_t idx;

	if (!self || !name)
		return sample;

	idx = hkl_sample_list_get_idx_from_name(self, name);
	if (HKL_FAIL != idx)
		sample = self->samples[idx];

	return sample;
}

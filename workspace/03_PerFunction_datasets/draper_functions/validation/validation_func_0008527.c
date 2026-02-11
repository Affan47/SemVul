smf_set_format(smf_t *smf, int format)
{
	assert(format == 0 || format == 1);

	if (smf->number_of_tracks > 1 && format == 0) {
		g_critical("There is more than one track, cannot set format to 0.");
		return (-1);
	}

	smf->format = format;

	return (0);
}

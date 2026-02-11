add_stderr(void)
{
    int i;

    for (i = 0; i < num_logfiles; ++i)
	if (logfiles[i].file == stderr)
	    return;
    logfiles[num_logfiles].file = stderr;
    logfiles[num_logfiles].minimum_output_level = GW_DEBUG;
    logfiles[num_logfiles].exclusive = GW_NON_EXCL;
    ++num_logfiles;
}

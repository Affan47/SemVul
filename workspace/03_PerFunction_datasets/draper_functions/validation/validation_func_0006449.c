in_frame_list(struct Option *opt, char *padname)
{
    int n;

    if (opt->answers)
	for (n = 0; opt->answers[n] != NULL; n++)
	    if (!strcmp(opt->answers[n], padname))
		return (1);

    return (0);
}

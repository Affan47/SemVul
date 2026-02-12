complain_about_duplicate(opts, iscompound)
const char *opts;
int iscompound;
{
#if defined(MAC)


	return;
#endif

	raw_printf(
		"\nWarning - %s option specified multiple times: %s.\n",
		iscompound ? "compound" : "boolean", opts);
	wait_synch();
	return;
}

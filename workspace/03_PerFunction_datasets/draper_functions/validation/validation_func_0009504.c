set_forward_delay(const char *name, unsigned int delay)
{
	FILE *f;
	char *forward_delay_path;

	forward_delay_path =
		g_strdup_printf("/sys/class/net/%s/bridge/forward_delay", name);

	if (forward_delay_path == NULL)
		return -ENOMEM;

	f = fopen(forward_delay_path, "r+");

	g_free(forward_delay_path);

	if (f == NULL)
		return -errno;

	fprintf(f, "%d", delay);

	fclose(f);

	return 0;
}

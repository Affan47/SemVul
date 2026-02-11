set_mode(int majour_mode, int minour_mode, struct _config *config)
{
	if (config->mode != 0)
		exit_error("Too many convertion mode arguments!");

	config->mode = majour_mode;
	config->mode2 = minour_mode;
}

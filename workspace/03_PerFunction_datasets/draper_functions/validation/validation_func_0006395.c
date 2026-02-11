image_version_file(const char *input)
{
	FILE *fcfg;
	int version;
	int ret;

	fcfg = fopen(input, "r");
	if (!fcfg) {
		fprintf(stderr, "Could not open input file %s\n", input);
		return -1;
	}

	image_cfg = malloc(IMAGE_CFG_ELEMENT_MAX *
			   sizeof(struct image_cfg_element));
	if (!image_cfg) {
		fprintf(stderr, "Cannot allocate memory\n");
		fclose(fcfg);
		return -1;
	}

	memset(image_cfg, 0,
	       IMAGE_CFG_ELEMENT_MAX * sizeof(struct image_cfg_element));
	rewind(fcfg);

	ret = image_create_config_parse(fcfg);
	fclose(fcfg);
	if (ret) {
		free(image_cfg);
		return -1;
	}

	version = image_get_version();

	if (version == -1)
		version = 0;

	free(image_cfg);

	return version;
}

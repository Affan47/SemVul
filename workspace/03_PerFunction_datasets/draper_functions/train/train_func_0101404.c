read_atlas_header(const char *buf, char *path)
{
	int width, height;
	if (!sscanf(buf, "* %s size %d %d", path, &width, &height))
		return 1;

	return 0;
}

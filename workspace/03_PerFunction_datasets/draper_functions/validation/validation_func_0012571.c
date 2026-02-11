lineno_width(int lines)
{
	int i, width;

	for (width = 1, i = 10; i <= lines + 1; width++)
		i *= 10;
	return width;
}

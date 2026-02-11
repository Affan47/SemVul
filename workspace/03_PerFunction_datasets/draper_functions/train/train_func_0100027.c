write_rgb_data (char *name, unsigned char *image, SANE_Int width,
		SANE_Int height)
{
  FILE *fdbg = NULL;

  fdbg = fopen (name, "wb");
  if (fdbg == NULL)
    return;
  fprintf (fdbg, "P6\n%d %d\n255\n", width, height);
  fwrite (image, width * 3, height, fdbg);
  fclose (fdbg);
}

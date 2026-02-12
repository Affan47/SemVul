read_colormap (tga_source_ptr sinfo, int cmaplen, int mapentrysize)

{
  int i;


  if (mapentrysize != 24)
    ERREXIT(sinfo->cinfo, JERR_TGA_BADCMAP);

  for (i = 0; i < cmaplen; i++) {
    sinfo->colormap[2][i] = (JSAMPLE) read_byte(sinfo);
    sinfo->colormap[1][i] = (JSAMPLE) read_byte(sinfo);
    sinfo->colormap[0][i] = (JSAMPLE) read_byte(sinfo);
  }
}

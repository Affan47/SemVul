write_os2_header (j_decompress_ptr cinfo, bmp_dest_ptr dest)

{
  char bmpfileheader[14];
  char bmpcoreheader[12];
  long headersize, bfSize;
  int bits_per_pixel, cmap_entries;


  if (cinfo->out_color_space == JCS_RGB ||
      (cinfo->out_color_space >= JCS_EXT_RGB &&
       cinfo->out_color_space <= JCS_EXT_ARGB)) {
    if (cinfo->quantize_colors) {

      bits_per_pixel = 8;
      cmap_entries = 256;
    } else {

      bits_per_pixel = 24;
      cmap_entries = 0;
    }
  } else if (cinfo->out_color_space == JCS_RGB565 ||
             cinfo->out_color_space == JCS_CMYK) {
    bits_per_pixel = 24;
    cmap_entries   = 0;
  } else {

    bits_per_pixel = 8;
    cmap_entries = 256;
  }

  headersize = 14 + 12 + cmap_entries * 3;
  bfSize = headersize + (long) dest->row_width * (long) cinfo->output_height;


  MEMZERO(bmpfileheader, sizeof(bmpfileheader));
  MEMZERO(bmpcoreheader, sizeof(bmpcoreheader));


  bmpfileheader[0] = 0x42;
  bmpfileheader[1] = 0x4D;
  PUT_4B(bmpfileheader, 2, bfSize);

  PUT_4B(bmpfileheader, 10, headersize);


  PUT_2B(bmpcoreheader, 0, 12);
  PUT_2B(bmpcoreheader, 4, cinfo->output_width);
  PUT_2B(bmpcoreheader, 6, cinfo->output_height);
  PUT_2B(bmpcoreheader, 8, 1);
  PUT_2B(bmpcoreheader, 10, bits_per_pixel);

  if (JFWRITE(dest->pub.output_file, bmpfileheader, 14) != (size_t) 14)
    ERREXIT(cinfo, JERR_FILE_WRITE);
  if (JFWRITE(dest->pub.output_file, bmpcoreheader, 12) != (size_t) 12)
    ERREXIT(cinfo, JERR_FILE_WRITE);

  if (cmap_entries > 0)
    write_colormap(cinfo, dest, cmap_entries, 3);
}

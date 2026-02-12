get_8bit_row (j_compress_ptr cinfo, cjpeg_source_ptr sinfo)

{
  tga_source_ptr source = (tga_source_ptr) sinfo;
  register int t;
  register JSAMPROW ptr;
  register JDIMENSION col;
  register JSAMPARRAY colormap = source->colormap;

  ptr = source->pub.buffer[0];
  for (col = cinfo->image_width; col > 0; col--) {
    (*source->read_pixel) (source);
    t = UCH(source->tga_pixel[0]);
    *ptr++ = colormap[0][t];
    *ptr++ = colormap[1][t];
    *ptr++ = colormap[2][t];
  }
  return 1;
}

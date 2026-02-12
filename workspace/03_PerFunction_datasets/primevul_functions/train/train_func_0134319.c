get_16bit_row (j_compress_ptr cinfo, cjpeg_source_ptr sinfo)

{
  tga_source_ptr source = (tga_source_ptr) sinfo;
  register int t;
  register JSAMPROW ptr;
  register JDIMENSION col;

  ptr = source->pub.buffer[0];
  for (col = cinfo->image_width; col > 0; col--) {
    (*source->read_pixel) (source);
    t = UCH(source->tga_pixel[0]);
    t += UCH(source->tga_pixel[1]) << 8;


    ptr[2] = (JSAMPLE) c5to8bits[t & 0x1F];
    t >>= 5;
    ptr[1] = (JSAMPLE) c5to8bits[t & 0x1F];
    t >>= 5;
    ptr[0] = (JSAMPLE) c5to8bits[t & 0x1F];
    ptr += 3;
  }
  return 1;
}

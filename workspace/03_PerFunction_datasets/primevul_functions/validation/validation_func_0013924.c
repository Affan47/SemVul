get_interlaced_row(j_compress_ptr cinfo, cjpeg_source_ptr sinfo)
{
  gif_source_ptr source = (gif_source_ptr)sinfo;
  register int c;
  register JSAMPROW sptr, ptr;
  register JDIMENSION col;
  register JSAMPARRAY colormap = source->colormap;
  JDIMENSION irow;


  switch ((int)(source->cur_row_number & 7)) {
  case 0:
    irow = source->cur_row_number >> 3;
    break;
  case 4:
    irow = (source->cur_row_number >> 3) + source->pass2_offset;
    break;
  case 2:
  case 6:
    irow = (source->cur_row_number >> 2) + source->pass3_offset;
    break;
  default:
    irow = (source->cur_row_number >> 1) + source->pass4_offset;
  }
  sptr = *(*cinfo->mem->access_virt_sarray)
    ((j_common_ptr)cinfo, source->interlaced_image, irow, (JDIMENSION)1,
     FALSE);

  ptr = source->pub.buffer[0];
  for (col = cinfo->image_width; col > 0; col--) {
    c = *sptr++;
    *ptr++ = colormap[CM_RED][c];
    *ptr++ = colormap[CM_GREEN][c];
    *ptr++ = colormap[CM_BLUE][c];
  }
  source->cur_row_number++;
  return 1;
}

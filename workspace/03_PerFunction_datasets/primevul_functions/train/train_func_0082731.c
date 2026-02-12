start_input_tga (j_compress_ptr cinfo, cjpeg_source_ptr sinfo)
{
  tga_source_ptr source = (tga_source_ptr) sinfo;
  U_CHAR targaheader[18];
  int idlen, cmaptype, subtype, flags, interlace_type, components;
  unsigned int width, height, maplen;
  boolean is_bottom_up;

#define GET_2B(offset)  ((unsigned int) UCH(targaheader[offset]) + \
                         (((unsigned int) UCH(targaheader[offset+1])) << 8))

  if (! ReadOK(source->pub.input_file, targaheader, 18))
    ERREXIT(cinfo, JERR_INPUT_EOF);


  if (targaheader[16] == 15)
    targaheader[16] = 16;

  idlen = UCH(targaheader[0]);
  cmaptype = UCH(targaheader[1]);
  subtype = UCH(targaheader[2]);
  maplen = GET_2B(5);
  width = GET_2B(12);
  height = GET_2B(14);
  source->pixel_size = UCH(targaheader[16]) >> 3;
  flags = UCH(targaheader[17]);

  is_bottom_up = ((flags & 0x20) == 0);
  interlace_type = flags >> 6;

  if (cmaptype > 1 ||
      source->pixel_size < 1 || source->pixel_size > 4 ||
      (UCH(targaheader[16]) & 7) != 0 ||
      interlace_type != 0)
    ERREXIT(cinfo, JERR_TGA_BADPARMS);

  if (subtype > 8) {

    source->read_pixel = read_rle_pixel;
    source->block_count = source->dup_pixel_count = 0;
    subtype -= 8;
  } else {

    source->read_pixel = read_non_rle_pixel;
  }


  components = 3;
  cinfo->in_color_space = JCS_RGB;

  switch (subtype) {
  case 1:
    if (source->pixel_size == 1 && cmaptype == 1)
      source->get_pixel_rows = get_8bit_row;
    else
      ERREXIT(cinfo, JERR_TGA_BADPARMS);
    TRACEMS2(cinfo, 1, JTRC_TGA_MAPPED, width, height);
    break;
  case 2:
    switch (source->pixel_size) {
    case 2:
      source->get_pixel_rows = get_16bit_row;
      break;
    case 3:
      source->get_pixel_rows = get_24bit_row;
      break;
    case 4:
      source->get_pixel_rows = get_32bit_row;
      break;
    default:
      ERREXIT(cinfo, JERR_TGA_BADPARMS);
      break;
    }
    TRACEMS2(cinfo, 1, JTRC_TGA, width, height);
    break;
  case 3:
    components = 1;
    cinfo->in_color_space = JCS_GRAYSCALE;
    if (source->pixel_size == 1)
      source->get_pixel_rows = get_8bit_gray_row;
    else
      ERREXIT(cinfo, JERR_TGA_BADPARMS);
    TRACEMS2(cinfo, 1, JTRC_TGA_GRAY, width, height);
    break;
  default:
    ERREXIT(cinfo, JERR_TGA_BADPARMS);
    break;
  }

  if (is_bottom_up) {

    source->whole_image = (*cinfo->mem->request_virt_sarray)
      ((j_common_ptr) cinfo, JPOOL_IMAGE, FALSE,
       (JDIMENSION) width * components, (JDIMENSION) height, (JDIMENSION) 1);
    if (cinfo->progress != NULL) {
      cd_progress_ptr progress = (cd_progress_ptr) cinfo->progress;
      progress->total_extra_passes++;
    }

    source->pub.buffer_height = 1;
    source->pub.get_pixel_rows = preload_image;
  } else {

    source->whole_image = NULL;
    source->pub.buffer = (*cinfo->mem->alloc_sarray)
      ((j_common_ptr) cinfo, JPOOL_IMAGE,
       (JDIMENSION) width * components, (JDIMENSION) 1);
    source->pub.buffer_height = 1;
    source->pub.get_pixel_rows = source->get_pixel_rows;
  }

  while (idlen--)
    (void) read_byte(source);

  if (maplen > 0) {
    if (maplen > 256 || GET_2B(3) != 0)
      ERREXIT(cinfo, JERR_TGA_BADCMAP);

    source->colormap = (*cinfo->mem->alloc_sarray)
      ((j_common_ptr) cinfo, JPOOL_IMAGE, (JDIMENSION) maplen, (JDIMENSION) 3);

    read_colormap(source, (int) maplen, UCH(targaheader[7]));
  } else {
    if (cmaptype)
      ERREXIT(cinfo, JERR_TGA_BADPARMS);
    source->colormap = NULL;
  }

  cinfo->input_components = components;
  cinfo->data_precision = 8;
  cinfo->image_width = width;
  cinfo->image_height = height;
}

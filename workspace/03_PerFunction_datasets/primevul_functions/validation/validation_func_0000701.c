start_input_gif(j_compress_ptr cinfo, cjpeg_source_ptr sinfo)
{
  gif_source_ptr source = (gif_source_ptr)sinfo;
  U_CHAR hdrbuf[10];
  unsigned int width, height;
  int colormaplen, aspectRatio;
  int c;


  if (!ReadOK(source->pub.input_file, hdrbuf, 6))
    ERREXIT(cinfo, JERR_GIF_NOT);
  if (hdrbuf[0] != 'G' || hdrbuf[1] != 'I' || hdrbuf[2] != 'F')
    ERREXIT(cinfo, JERR_GIF_NOT);


  if ((hdrbuf[3] != '8' || hdrbuf[4] != '7' || hdrbuf[5] != 'a') &&
      (hdrbuf[3] != '8' || hdrbuf[4] != '9' || hdrbuf[5] != 'a'))
    TRACEMS3(cinfo, 1, JTRC_GIF_BADVERSION, hdrbuf[3], hdrbuf[4], hdrbuf[5]);


  if (!ReadOK(source->pub.input_file, hdrbuf, 7))
    ERREXIT(cinfo, JERR_INPUT_EOF);
  width = LM_to_uint(hdrbuf, 0);
  height = LM_to_uint(hdrbuf, 2);

  aspectRatio = UCH(hdrbuf[6]);
  if (aspectRatio != 0 && aspectRatio != 49)
    TRACEMS(cinfo, 1, JTRC_GIF_NONSQUARE);


  source->colormap = (*cinfo->mem->alloc_sarray)
    ((j_common_ptr)cinfo, JPOOL_IMAGE, (JDIMENSION)MAXCOLORMAPSIZE,
     (JDIMENSION)NUMCOLORS);
  colormaplen = 0;


  if (BitSet(hdrbuf[4], COLORMAPFLAG)) {
    colormaplen = 2 << (hdrbuf[4] & 0x07);
    ReadColorMap(source, colormaplen, source->colormap);
  }


  for (;;) {
    c = ReadByte(source);

    if (c == ';')
      ERREXIT(cinfo, JERR_GIF_IMAGENOTFOUND);

    if (c == '!') {
      DoExtension(source);
      continue;
    }

    if (c != ',') {
      WARNMS1(cinfo, JWRN_GIF_CHAR, c);
      continue;
    }


    if (!ReadOK(source->pub.input_file, hdrbuf, 9))
      ERREXIT(cinfo, JERR_INPUT_EOF);

    width = LM_to_uint(hdrbuf, 4);
    height = LM_to_uint(hdrbuf, 6);
    source->is_interlaced = (BitSet(hdrbuf[8], INTERLACE) != 0);


    if (BitSet(hdrbuf[8], COLORMAPFLAG)) {
      colormaplen = 2 << (hdrbuf[8] & 0x07);
      ReadColorMap(source, colormaplen, source->colormap);
    }

    source->input_code_size = ReadByte(source);
    if (source->input_code_size < 2 || source->input_code_size > 8)
      ERREXIT1(cinfo, JERR_GIF_CODESIZE, source->input_code_size);


    break;
  }


  source->symbol_head = (UINT16 *)
    (*cinfo->mem->alloc_large) ((j_common_ptr)cinfo, JPOOL_IMAGE,
                                LZW_TABLE_SIZE * sizeof(UINT16));
  source->symbol_tail = (UINT8 *)
    (*cinfo->mem->alloc_large) ((j_common_ptr)cinfo, JPOOL_IMAGE,
                                LZW_TABLE_SIZE * sizeof(UINT8));
  source->symbol_stack = (UINT8 *)
    (*cinfo->mem->alloc_large) ((j_common_ptr)cinfo, JPOOL_IMAGE,
                                LZW_TABLE_SIZE * sizeof(UINT8));
  InitLZWCode(source);


  if (source->is_interlaced) {


    source->interlaced_image = (*cinfo->mem->request_virt_sarray)
      ((j_common_ptr)cinfo, JPOOL_IMAGE, FALSE,
       (JDIMENSION)width, (JDIMENSION)height, (JDIMENSION)1);
    if (cinfo->progress != NULL) {
      cd_progress_ptr progress = (cd_progress_ptr)cinfo->progress;
      progress->total_extra_passes++;
    }
    source->pub.get_pixel_rows = load_interlaced_image;
  } else {
    source->pub.get_pixel_rows = get_pixel_rows;
  }


  source->pub.buffer = (*cinfo->mem->alloc_sarray)
    ((j_common_ptr)cinfo, JPOOL_IMAGE, (JDIMENSION)width * NUMCOLORS,
     (JDIMENSION)1);
  source->pub.buffer_height = 1;


  for (c = colormaplen; c < source->clear_code; c++) {
    source->colormap[CM_RED][c]   =
    source->colormap[CM_GREEN][c] =
    source->colormap[CM_BLUE][c]  = CENTERJSAMPLE;
  }


  cinfo->in_color_space = JCS_RGB;
  cinfo->input_components = NUMCOLORS;
  cinfo->data_precision = BITS_IN_JSAMPLE;
  cinfo->image_width = width;
  cinfo->image_height = height;

  TRACEMS3(cinfo, 1, JTRC_GIF, width, height, colormaplen);
}

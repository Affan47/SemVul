create_colormap (j_decompress_ptr cinfo)
{
  my_cquantize_ptr cquantize = (my_cquantize_ptr) cinfo->cquantize;
  JSAMPARRAY colormap;
  int total_colors;
  int i,j,k, nci, blksize, blkdist, ptr, val;


  total_colors = select_ncolors(cinfo, cquantize->Ncolors);


  if (cinfo->out_color_components == 3)
    TRACEMS4(cinfo, 1, JTRC_QUANT_3_NCOLORS,
	     total_colors, cquantize->Ncolors[0],
	     cquantize->Ncolors[1], cquantize->Ncolors[2]);
  else
    TRACEMS1(cinfo, 1, JTRC_QUANT_NCOLORS, total_colors);


  colormap = (*cinfo->mem->alloc_sarray)
    ((j_common_ptr) cinfo, JPOOL_IMAGE,
     (JDIMENSION) total_colors, (JDIMENSION) cinfo->out_color_components);


  blkdist = total_colors;

  for (i = 0; i < cinfo->out_color_components; i++) {

    nci = cquantize->Ncolors[i];
    blksize = blkdist / nci;
    for (j = 0; j < nci; j++) {

      val = output_value(cinfo, i, j, nci-1);

      for (ptr = j * blksize; ptr < total_colors; ptr += blkdist) {

	for (k = 0; k < blksize; k++)
	  colormap[i][ptr+k] = (JSAMPLE) val;
      }
    }
    blkdist = blksize;
  }


  cquantize->sv_colormap = colormap;
  cquantize->sv_actual = total_colors;
}

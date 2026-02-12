get_memory_row (j_compress_ptr cinfo, cjpeg_source_ptr sinfo)
{
  tga_source_ptr source = (tga_source_ptr) sinfo;
  JDIMENSION source_row;


  source_row = cinfo->image_height - source->current_row - 1;


  source->pub.buffer = (*cinfo->mem->access_virt_sarray)
    ((j_common_ptr) cinfo, source->whole_image,
     source_row, (JDIMENSION) 1, FALSE);

  source->current_row++;
  return 1;
}

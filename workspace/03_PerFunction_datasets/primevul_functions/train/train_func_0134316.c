jinit_read_targa (j_compress_ptr cinfo)
{
  tga_source_ptr source;


  source = (tga_source_ptr)
      (*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_IMAGE,
                                  sizeof(tga_source_struct));
  source->cinfo = cinfo;

  source->pub.start_input = start_input_tga;
  source->pub.finish_input = finish_input_tga;

  return (cjpeg_source_ptr) source;
}

jinit_read_gif(j_compress_ptr cinfo)
{
  gif_source_ptr source;


  source = (gif_source_ptr)
    (*cinfo->mem->alloc_small) ((j_common_ptr)cinfo, JPOOL_IMAGE,
                                sizeof(gif_source_struct));
  source->cinfo = cinfo;

  source->pub.start_input = start_input_gif;
  source->pub.finish_input = finish_input_gif;

  return (cjpeg_source_ptr)source;
}

jinit_arith_encoder (j_compress_ptr cinfo)
{
  arith_entropy_ptr entropy;
  int i;

  entropy = (arith_entropy_ptr)
    (*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_IMAGE,
				SIZEOF(arith_entropy_encoder));
  cinfo->entropy = (struct jpeg_entropy_encoder *) entropy;
  entropy->pub.start_pass = start_pass;
  entropy->pub.finish_pass = finish_pass;


  for (i = 0; i < NUM_ARITH_TBLS; i++) {
    entropy->dc_stats[i] = NULL;
    entropy->ac_stats[i] = NULL;
  }
}

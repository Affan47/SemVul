jinit_huff_encoder (j_compress_ptr cinfo)
{
  huff_entropy_ptr entropy;
  int i;

  entropy = (huff_entropy_ptr)
    (*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_IMAGE,
				SIZEOF(huff_entropy_encoder));
  cinfo->entropy = (struct jpeg_entropy_encoder *) entropy;
  entropy->pub.start_pass = start_pass_huff;

  if (cinfo->progressive_mode) {

    for (i = 0; i < NUM_HUFF_TBLS; i++) {
      entropy->derived_tbls[i] = NULL;
      entropy->count_ptrs[i] = NULL;
    }
    entropy->bit_buffer = NULL;
  } else {

    for (i = 0; i < NUM_HUFF_TBLS; i++) {
      entropy->dc_derived_tbls[i] = entropy->ac_derived_tbls[i] = NULL;
      entropy->dc_count_ptrs[i] = entropy->ac_count_ptrs[i] = NULL;
    }
  }
}

finish_pass_gather (j_compress_ptr cinfo)
{
  j_lossless_c_ptr losslsc = (j_lossless_c_ptr) cinfo->codec;
  lhuff_entropy_ptr entropy = (lhuff_entropy_ptr) losslsc->entropy_private;
  int ci, dctbl;
  jpeg_component_info * compptr;
  JHUFF_TBL **htblptr;
  boolean did_dc[NUM_HUFF_TBLS];


  MEMZERO(did_dc, SIZEOF(did_dc));

  for (ci = 0; ci < cinfo->comps_in_scan; ci++) {
    compptr = cinfo->cur_comp_info[ci];
    dctbl = compptr->dc_tbl_no;
    if (! did_dc[dctbl]) {
      htblptr = & cinfo->dc_huff_tbl_ptrs[dctbl];
      if (*htblptr == NULL)
  *htblptr = jpeg_alloc_huff_table((j_common_ptr) cinfo);
      jpeg_gen_optimal_table(cinfo, *htblptr, entropy->count_ptrs[dctbl]);
      did_dc[dctbl] = TRUE;
    }
  }
}

increment_simple_rowgroup_ctr(j_decompress_ptr cinfo, JDIMENSION rows)
{
  JDIMENSION rows_left;
  my_main_ptr main_ptr = (my_main_ptr)cinfo->main;
  my_master_ptr master = (my_master_ptr)cinfo->master;

  if (master->using_merged_upsample && cinfo->max_v_samp_factor == 2) {
    read_and_discard_scanlines(cinfo, rows);
    return;
  }


  main_ptr->rowgroup_ctr += rows / cinfo->max_v_samp_factor;


  rows_left = rows % cinfo->max_v_samp_factor;
  cinfo->output_scanline += rows - rows_left;

  read_and_discard_scanlines(cinfo, rows_left);
}

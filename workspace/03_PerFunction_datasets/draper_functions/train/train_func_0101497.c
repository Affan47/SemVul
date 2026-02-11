save_pre_frame( cpl_frame * frame, xsh_instrument * instrument,
  cpl_frame *B_frame)
{
  xsh_pre *pre = NULL;
  cpl_frame * res_frame = NULL ;
  const char * fname = NULL ;
  cpl_propertylist *list_B = NULL;
  const char * name_B = NULL;
  double ra_off_B, dec_off_B;
  double ra_cumoff_B, dec_cumoff_B;


  fname = cpl_frame_get_filename( frame);
  name_B = cpl_frame_get_filename( B_frame);
  check( pre = xsh_pre_load( frame, instrument));
  check( list_B = cpl_propertylist_load( name_B, 0));

  check( ra_off_B = xsh_pfits_get_ra_reloffset( list_B));
  check( dec_off_B = xsh_pfits_get_dec_reloffset( list_B));

  check( ra_cumoff_B = xsh_pfits_get_ra_cumoffset( list_B));
  check( dec_cumoff_B = xsh_pfits_get_dec_cumoffset( list_B));

  check( xsh_pfits_set_b_ra_reloffset( pre->data_header, ra_off_B));
  check( xsh_pfits_set_b_dec_reloffset( pre->data_header, dec_off_B));

  check( xsh_pfits_set_b_ra_cumoffset( pre->data_header, ra_cumoff_B));
  check( xsh_pfits_set_b_dec_cumoffset( pre->data_header, dec_cumoff_B));


  check( res_frame = xsh_pre_save( pre, fname, "FRAME_PRE_FORMAT", 1));

  cleanup:
    xsh_pre_free( &pre);
    xsh_free_propertylist( &list_B);
    xsh_free_frame( &res_frame);
    return;
}

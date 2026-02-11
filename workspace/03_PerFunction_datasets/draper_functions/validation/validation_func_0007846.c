jp2_read_jp(
          opj_jp2_t *jp2,
          unsigned char * p_header_data,
          unsigned int p_header_size,
          opj_event_mgr_t * p_manager
         )
{
  unsigned int l_magic_number;


  assert(p_header_data != 00);
  assert(jp2 != 00);
  assert(p_manager != 00);

  if
    (jp2->jp2_state != JP2_STATE_NONE)
  {
    opj_event_msg(p_manager, EVT_ERROR, "The signature box must be the first box in the file.\n");
    return false;
  }


  if
    (p_header_size != 4)
  {
    opj_event_msg(p_manager, EVT_ERROR, "Error with JP signature Box size\n");
    return false;
  }


  opj_read_bytes(p_header_data,&l_magic_number,4);
  if
    (l_magic_number != 0x0d0a870a )
  {
    opj_event_msg(p_manager, EVT_ERROR, "Error with JP Signature : bad magic number\n");
    return false;
  }
  jp2->jp2_state |= JP2_STATE_SIGNATURE;
  return true;
}

jp2_read_boxhdr_char(
                opj_jp2_box_t *box,
                OPJ_BYTE * p_data,
                OPJ_UINT32 * p_number_bytes_read,
                OPJ_UINT32 p_box_max_size,
                opj_event_mgr_t * p_manager
              )
{

  assert(p_data != 00);
  assert(box != 00);
  assert(p_number_bytes_read != 00);
  assert(p_manager != 00);

  if
    (p_box_max_size < 8)
  {
    opj_event_msg(p_manager, EVT_ERROR, "Cannot handle box of less than 8 bytes\n");
    return false;
  }

  opj_read_bytes(p_data,&(box->length), 4);
  p_data += 4;
  opj_read_bytes(p_data,&(box->type), 4);
  p_data += 4;
  *p_number_bytes_read = 8;


  if
    (box->length == 1)
  {
    unsigned int l_xl_part_size;
    if
      (p_box_max_size < 16)
    {
      opj_event_msg(p_manager, EVT_ERROR, "Cannot handle XL box of less than 16 bytes\n");
      return false;
    }

    opj_read_bytes(p_data,&l_xl_part_size, 4);
    p_data += 4;
    *p_number_bytes_read += 4;
    if
      (l_xl_part_size != 0)
    {
      opj_event_msg(p_manager, EVT_ERROR, "Cannot handle box sizes higher than 2^32\n");
      return false;
    }
    opj_read_bytes(p_data,&(box->length), 4);
    *p_number_bytes_read += 4;
    if
      (box->length == 0)
    {
      opj_event_msg(p_manager, EVT_ERROR, "Cannot handle box of undefined sizes\n");
      return false;
    }

  }
  else if
    (box->length == 0)
  {
    opj_event_msg(p_manager, EVT_ERROR, "Cannot handle box of undefined sizes\n");
    return false;
  }
  return true;
}

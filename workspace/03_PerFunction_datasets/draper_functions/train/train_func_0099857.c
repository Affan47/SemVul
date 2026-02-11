bgav_qt_rdrf_read(qt_atom_header_t * h,
                      bgav_input_context_t * input, qt_rdrf_t * ret)
  {
  if(!bgav_input_read_32_le(input, &ret->flags) ||
     !bgav_input_read_fourcc(input, &ret->fourcc) ||
     !bgav_input_read_fourcc(input, &ret->data_ref_size))
    return 0;

  ret->data_ref = malloc(ret->data_ref_size);
  if(bgav_input_read_data(input, ret->data_ref, ret->data_ref_size) <
     ret->data_ref_size)
    return 0;
  return 1;
  }

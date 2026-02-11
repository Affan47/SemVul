bgav_h264_slice_header_parse(const uint8_t * data, int len,
                                  const bgav_h264_sps_t * sps,
                                  bgav_h264_slice_header_t * ret)
  {
  bgav_bitstream_t b;
  bgav_bitstream_init(&b, data, len);

  memset(ret, 0, sizeof(*ret));

  bgav_bitstream_get_golomb_ue(&b, &ret->first_mb_in_slice);
  bgav_bitstream_get_golomb_ue(&b, &ret->slice_type);
  bgav_bitstream_get_golomb_ue(&b, &ret->pic_parameter_set_id);

  if(sps->separate_colour_plane_flag)
    bgav_bitstream_get(&b, &ret->colour_plane_id, 2);

  bgav_bitstream_get(&b, &ret->frame_num, sps->log2_max_frame_num_minus4+4);

  if(!sps->frame_mbs_only_flag)
    {
    bgav_bitstream_get(&b, &ret->field_pic_flag, 1);
    if(ret->field_pic_flag)
      bgav_bitstream_get(&b, &ret->bottom_field_flag, 1);
    }
  }

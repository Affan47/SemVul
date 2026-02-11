flv_tag_read(bgav_input_context_t * ctx, flv_tag * ret)
  {
  if(!bgav_input_read_data(ctx, &ret->type, 1) ||
     !bgav_input_read_24_be(ctx, &ret->data_size) ||
     !bgav_input_read_24_be(ctx, &ret->timestamp) ||
     !bgav_input_read_32_be(ctx, &ret->reserved))
    return 0;
  return 1;
  }

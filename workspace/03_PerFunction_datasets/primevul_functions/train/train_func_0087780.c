de265_error decoder_context::decode(int* more)
{
  decoder_context* ctx = this;


  if (ctx->nal_parser.get_NAL_queue_length() == 0 &&
      (ctx->nal_parser.is_end_of_stream() || ctx->nal_parser.is_end_of_frame()) &&
      ctx->image_units.empty()) {


    ctx->dpb.flush_reorder_buffer();

    if (more) { *more = ctx->dpb.num_pictures_in_output_queue(); }

    return DE265_OK;
  }


  if (ctx->nal_parser.is_end_of_stream() == false &&
      ctx->nal_parser.is_end_of_frame() == false &&
      ctx->nal_parser.get_NAL_queue_length() == 0) {
    if (more) { *more=1; }

    return DE265_ERROR_WAITING_FOR_INPUT_DATA;
  }


  if (!ctx->dpb.has_free_dpb_picture(false)) {
    if (more) *more = 1;
    return DE265_ERROR_IMAGE_BUFFER_FULL;
  }


  de265_error err = DE265_OK;
  bool did_work = false;

  if (ctx->nal_parser.get_NAL_queue_length()) {
    NAL_unit* nal = ctx->nal_parser.pop_from_NAL_queue();
    assert(nal);
    err = ctx->decode_NAL(nal);

    did_work=true;
  }
  else if (ctx->nal_parser.is_end_of_frame() == true &&
      ctx->image_units.empty()) {
    if (more) { *more=1; }

    return DE265_ERROR_WAITING_FOR_INPUT_DATA;
  }
  else {
    err = decode_some(&did_work);
  }

  if (more) {

    *more = (err==DE265_OK && did_work);
  }

  return err;
}

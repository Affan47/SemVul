Status ModularFrameDecoder::FinalizeDecoding(PassesDecoderState* dec_state,
                                             jxl::ThreadPool* pool,
                                             ImageBundle* output) {
  if (!use_full_image) return true;
  Image& gi = full_image;
  size_t xsize = gi.w;
  size_t ysize = gi.h;


  if (xsize * ysize < frame_dim.group_dim * frame_dim.group_dim) pool = nullptr;


  gi.undo_transforms(global_header.wp_header, -1, pool);
  if (gi.error) return JXL_FAILURE("Undoing transforms failed");

  auto& decoded = dec_state->decoded;

  JXL_RETURN_IF_ERROR(
      ModularImageToDecodedRect(gi, dec_state, pool, output, Rect(decoded)));
  return true;
}

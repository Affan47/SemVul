int Http2Session::OnHeaderCallback(nghttp2_session* handle,
                                   const nghttp2_frame* frame,
                                   nghttp2_rcbuf* name,
                                   nghttp2_rcbuf* value,
                                   uint8_t flags,
                                   void* user_data) {
  Http2Session* session = static_cast<Http2Session*>(user_data);
  int32_t id = GetFrameID(frame);
  Http2Stream* stream = session->FindStream(id);


  if (UNLIKELY(stream == nullptr))
    return NGHTTP2_ERR_TEMPORAL_CALLBACK_FAILURE;


  if (!stream->IsDestroyed() && !stream->AddHeader(name, value, flags)) {


    stream->SubmitRstStream(NGHTTP2_ENHANCE_YOUR_CALM);
    return NGHTTP2_ERR_TEMPORAL_CALLBACK_FAILURE;
  }
  return 0;
}

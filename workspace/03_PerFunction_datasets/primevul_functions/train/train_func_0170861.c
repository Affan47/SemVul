void Http2Stream::SubmitRstStream(const uint32_t code) {
  CHECK(!this->is_destroyed());
  code_ = code;

  auto is_stream_cancel = [](const uint32_t code) {
    return code == NGHTTP2_CANCEL;
  };


  if (session_->is_in_scope() && is_stream_cancel(code)) {
      session_->AddPendingRstStream(id_);
      return;
  }


  if (session_->SendPendingData() != 0) {
    session_->AddPendingRstStream(id_);
    return;
  }

  FlushRstStream();
}

void Http2Session::OnStreamRead(ssize_t nread, const uv_buf_t& buf_) {
  HandleScope handle_scope(env()->isolate());
  Context::Scope context_scope(env()->context());
  Http2Scope h2scope(this);
  CHECK_NOT_NULL(stream_);
  Debug(this, "receiving %d bytes, offset %d", nread, stream_buf_offset_);
  AllocatedBuffer buf(env(), buf_);


  if (nread <= 0) {
    if (nread < 0) {
      PassReadErrorToPreviousListener(nread);
    }
    return;
  }

  statistics_.data_received += nread;

  if (LIKELY(stream_buf_offset_ == 0)) {

    buf.Resize(nread);
  } else {


    size_t pending_len = stream_buf_.len - stream_buf_offset_;
    AllocatedBuffer new_buf =
        AllocatedBuffer::AllocateManaged(env(), pending_len + nread);
    memcpy(new_buf.data(), stream_buf_.base + stream_buf_offset_, pending_len);
    memcpy(new_buf.data() + pending_len, buf.data(), nread);

    buf = std::move(new_buf);
    nread = buf.size();
    stream_buf_offset_ = 0;
    stream_buf_ab_.Reset();


    DecrementCurrentSessionMemory(stream_buf_.len);
  }

  IncrementCurrentSessionMemory(nread);


  stream_buf_ = uv_buf_init(buf.data(), static_cast<unsigned int>(nread));


  stream_buf_allocation_ = std::move(buf);

  ConsumeHTTP2Data();

  MaybeStopReading();
}

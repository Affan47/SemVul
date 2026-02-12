void Http2Session::OnStreamRead(ssize_t nread, const uv_buf_t& buf_) {
  HandleScope handle_scope(env()->isolate());
  Context::Scope context_scope(env()->context());
  Http2Scope h2scope(this);
  CHECK_NOT_NULL(stream_);
  Debug(this, "receiving %d bytes", nread);


  if (nread <= 0) {
    free(buf_.base);
    if (nread < 0) {
      PassReadErrorToPreviousListener(nread);
    }
    return;
  }

  uv_buf_t buf = buf_;

  statistics_.data_received += nread;

  if (UNLIKELY(stream_buf_offset_ > 0)) {


    char* new_buf = Malloc(stream_buf_.len - stream_buf_offset_ + nread);
    memcpy(new_buf,
           stream_buf_.base + stream_buf_offset_,
           stream_buf_.len - stream_buf_offset_);
    memcpy(new_buf + stream_buf_.len - stream_buf_offset_,
           buf.base,
           nread);
    free(buf.base);
    nread = stream_buf_.len - stream_buf_offset_ + nread;
    buf = uv_buf_init(new_buf, nread);
    stream_buf_offset_ = 0;
    stream_buf_ab_.Reset();


    DecrementCurrentSessionMemory(stream_buf_.len);
  }


  buf.base = Realloc(buf.base, nread);
  IncrementCurrentSessionMemory(nread);


  stream_buf_ = uv_buf_init(buf.base, nread);


  CHECK_LE(static_cast<size_t>(nread), stream_buf_.len);

  Isolate* isolate = env()->isolate();


  stream_buf_allocation_ = buf;

  ssize_t ret = ConsumeHTTP2Data();

  if (UNLIKELY(ret < 0)) {
    Debug(this, "fatal error receiving data: %d", ret);
    Local<Value> arg = Integer::New(isolate, ret);
    MakeCallback(env()->error_string(), 1, &arg);
    return;
  }

  MaybeStopReading();
}

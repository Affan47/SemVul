void Http2Stream::Destroy() {

  if (IsDestroyed())
    return;
  if (session_->HasPendingRstStream(id_))
    FlushRstStream();
  flags_ |= NGHTTP2_STREAM_FLAG_DESTROYED;

  Debug(this, "destroying stream");


  env()->SetImmediate([](Environment* env, void* data) {
    Http2Stream* stream = static_cast<Http2Stream*>(data);


    while (!stream->queue_.empty()) {
      nghttp2_stream_write& head = stream->queue_.front();
      if (head.req_wrap != nullptr)
        head.req_wrap->Done(UV_ECANCELED);
      stream->queue_.pop();
    }


    if (stream->session() == nullptr ||
        !stream->session()->HasWritesOnSocketForStream(stream))
      delete stream;
  }, this, this->object());

  statistics_.end_time = uv_hrtime();
  session_->statistics_.stream_average_duration =
      ((statistics_.end_time - statistics_.start_time) /
          session_->statistics_.stream_count) / 1e6;
  EmitStatistics();
}

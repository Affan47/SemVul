void Http2Stream::Destroy() {

  if (is_destroyed())
    return;
  if (session_->has_pending_rststream(id_))
    FlushRstStream();
  set_destroyed();

  Debug(this, "destroying stream");


  BaseObjectPtr<Http2Stream> strong_ref = session_->RemoveStream(id_);
  if (strong_ref) {
    env()->SetImmediate([this, strong_ref = std::move(strong_ref)](
        Environment* env) {


      while (!queue_.empty()) {
        NgHttp2StreamWrite& head = queue_.front();
        if (head.req_wrap)
          WriteWrap::FromObject(head.req_wrap)->Done(UV_ECANCELED);
        queue_.pop();
      }


      if (session() == nullptr ||
          !session()->HasWritesOnSocketForStream(this)) {

        Detach();
      }
    });
  }

  statistics_.end_time = uv_hrtime();
  session_->statistics_.stream_average_duration =
      ((statistics_.end_time - statistics_.start_time) /
          session_->statistics_.stream_count) / 1e6;
  EmitStatistics();
}

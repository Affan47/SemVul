void Http2Session::Close(uint32_t code, bool socket_closed) {
  Debug(this, "closing session");

  if (is_closing())
    return;
  set_closing();


  if (stream_ != nullptr) {
    set_reading_stopped();
    stream_->ReadStop();
  }


  if (!socket_closed) {
    Debug(this, "terminating session with code %d", code);
    CHECK_EQ(nghttp2_session_terminate_session(session_.get(), code), 0);
    SendPendingData();
  } else if (stream_ != nullptr) {
    stream_->RemoveStreamListener(this);
  }

  set_destroyed();


  if (!is_write_in_progress()) {
    Debug(this, "make done session callback");
    HandleScope scope(env()->isolate());
    MakeCallback(env()->ondone_string(), 0, nullptr);
  }


  while (BaseObjectPtr<Http2Ping> ping = PopPing()) {
    ping->DetachFromSession();
    env()->SetImmediate(
        [ping = std::move(ping)](Environment* env) {
          ping->Done(false);
        });
  }

  statistics_.end_time = uv_hrtime();
  EmitStatistics();
}

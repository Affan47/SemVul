void Http2Session::OnStreamAfterWrite(WriteWrap* w, int status) {
  Debug(this, "write finished with status %d", status);

  CHECK_NE(flags_ & SESSION_STATE_WRITE_IN_PROGRESS, 0);
  flags_ &= ~SESSION_STATE_WRITE_IN_PROGRESS;


  ClearOutgoing(status);

  if ((flags_ & SESSION_STATE_READING_STOPPED) &&
      !(flags_ & SESSION_STATE_WRITE_IN_PROGRESS) &&
      nghttp2_session_want_read(session_)) {
    flags_ &= ~SESSION_STATE_READING_STOPPED;
    stream_->ReadStart();
  }


  if (stream_buf_offset_ > 0) {
    ConsumeHTTP2Data();
  }

  if (!(flags_ & SESSION_STATE_WRITE_SCHEDULED)) {

    MaybeScheduleWrite();
  }
}

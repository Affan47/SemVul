CreateSrtpSessions() {
  send_session_.reset(new SrtpSession());
  recv_session_.reset(new SrtpSession());
  SignalSrtpError.repeat(send_session_->SignalSrtpError);
  SignalSrtpError.repeat(recv_session_->SignalSrtpError);

  send_session_->set_signal_silent_time(signal_silent_time_in_ms_);
  recv_session_->set_signal_silent_time(signal_silent_time_in_ms_);
}

Http2Scope::Http2Scope(Http2Session* session) : session_(session) {
  if (!session_) return;


  if (session_->is_in_scope() || session_->is_write_scheduled()) {
    session_.reset();
    return;
  }
  session_->set_in_scope();
}

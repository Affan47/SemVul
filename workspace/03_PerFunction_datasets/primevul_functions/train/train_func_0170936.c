void Http2Session::MaybeScheduleWrite() {
  CHECK(!is_write_scheduled());
  if (UNLIKELY(!session_))
    return;

  if (nghttp2_session_want_write(session_.get())) {
    HandleScope handle_scope(env()->isolate());
    Debug(this, "scheduling write");
    set_write_scheduled();
    BaseObjectPtr<Http2Session> strong_ref{this};
    env()->SetImmediate([this, strong_ref](Environment* env) {
      if (!session_ || !is_write_scheduled()) {


        return;
      }


      HandleScope handle_scope(env->isolate());
      InternalCallbackScope callback_scope(this);
      SendPendingData();
    });
  }
}

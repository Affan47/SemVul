void Http2Session::MaybeScheduleWrite() {
  CHECK_EQ(flags_ & SESSION_STATE_WRITE_SCHEDULED, 0);
  if (UNLIKELY(session_ == nullptr))
    return;

  if (nghttp2_session_want_write(session_)) {
    HandleScope handle_scope(env()->isolate());
    Debug(this, "scheduling write");
    flags_ |= SESSION_STATE_WRITE_SCHEDULED;
    env()->SetImmediate([](Environment* env, void* data) {
      Http2Session* session = static_cast<Http2Session*>(data);
      if (session->session_ == nullptr ||
          !(session->flags_ & SESSION_STATE_WRITE_SCHEDULED)) {


        return;
      }


      HandleScope handle_scope(env->isolate());
      InternalCallbackScope callback_scope(session);
      session->SendPendingData();
    }, static_cast<void*>(this), object());
  }
}

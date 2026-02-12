void Http2Session::HandleSettingsFrame(const nghttp2_frame* frame) {
  bool ack = frame->hd.flags & NGHTTP2_FLAG_ACK;
  if (!ack) {
    js_fields_->bitfield &= ~(1 << kSessionRemoteSettingsIsUpToDate);
    if (!(js_fields_->bitfield & (1 << kSessionHasRemoteSettingsListeners)))
      return;

    MakeCallback(env()->http2session_on_settings_function(), 0, nullptr);
    return;
  }


  BaseObjectPtr<Http2Settings> settings = PopSettings();
  if (settings) {
    settings->Done(true);
    return;
  }


  Isolate* isolate = env()->isolate();
  HandleScope scope(isolate);
  Local<Context> context = env()->context();
  Context::Scope context_scope(context);
  Local<Value> arg = Integer::New(isolate, NGHTTP2_ERR_PROTO);
  MakeCallback(env()->http2session_on_error_function(), 1, &arg);
}

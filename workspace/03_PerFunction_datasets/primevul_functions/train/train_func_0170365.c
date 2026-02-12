void Http2Session::HandleSettingsFrame(const nghttp2_frame* frame) {
  bool ack = frame->hd.flags & NGHTTP2_FLAG_ACK;
  if (!ack) {
    js_fields_[kBitfield] &= ~(1 << kSessionRemoteSettingsIsUpToDate);
    if (!(js_fields_[kBitfield] & (1 << kSessionHasRemoteSettingsListeners)))
      return;

    MakeCallback(env()->onsettings_string(), 0, nullptr);
    return;
  }


  Http2Settings* settings = PopSettings();
  if (settings != nullptr) {
    settings->Done(true);
    return;
  }


  Isolate* isolate = env()->isolate();
  HandleScope scope(isolate);
  Local<Context> context = env()->context();
  Context::Scope context_scope(context);
  Local<Value> arg = Integer::New(isolate, NGHTTP2_ERR_PROTO);
  MakeCallback(env()->error_string(), 1, &arg);
}

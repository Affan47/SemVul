int Http2Session::OnStreamClose(nghttp2_session* handle,
                                int32_t id,
                                uint32_t code,
                                void* user_data) {
  Http2Session* session = static_cast<Http2Session*>(user_data);
  Environment* env = session->env();
  Isolate* isolate = env->isolate();
  HandleScope scope(isolate);
  Local<Context> context = env->context();
  Context::Scope context_scope(context);
  Debug(session, "stream %d closed with code: %d", id, code);
  BaseObjectPtr<Http2Stream> stream = session->FindStream(id);


  if (!stream || stream->is_destroyed())
    return 0;

  stream->Close(code);


  Local<Value> arg = Integer::NewFromUnsigned(isolate, code);
  MaybeLocal<Value> answer =
    stream->MakeCallback(env->http2session_on_stream_close_function(),
                          1, &arg);
  if (answer.IsEmpty() || answer.ToLocalChecked()->IsFalse()) {

    stream->Destroy();
  }
  return 0;
}

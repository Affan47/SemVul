void Http2StreamListener::OnStreamRead(ssize_t nread, const uv_buf_t& buf) {
  Http2Stream* stream = static_cast<Http2Stream*>(stream_);
  Http2Session* session = stream->session();
  Environment* env = stream->env();
  HandleScope handle_scope(env->isolate());
  Context::Scope context_scope(env->context());

  if (nread < 0) {
    PassReadErrorToPreviousListener(nread);
    return;
  }

  Local<ArrayBuffer> ab;
  if (session->stream_buf_ab_.IsEmpty()) {
    ab = ArrayBuffer::New(env->isolate(),
                          session->stream_buf_allocation_.base,
                          session->stream_buf_allocation_.len,
                          v8::ArrayBufferCreationMode::kInternalized);
    session->stream_buf_allocation_ = uv_buf_init(nullptr, 0);
    session->stream_buf_ab_.Reset(env->isolate(), ab);
  } else {
    ab = session->stream_buf_ab_.Get(env->isolate());
  }


  size_t offset = buf.base - session->stream_buf_.base;


  CHECK_GE(offset, session->stream_buf_offset_);
  CHECK_LE(offset, session->stream_buf_.len);
  CHECK_LE(offset + buf.len, session->stream_buf_.len);

  Local<Object> buffer =
      Buffer::New(env, ab, offset, nread).ToLocalChecked();

  stream->CallJSOnreadMethod(nread, buffer);
}

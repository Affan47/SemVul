void Http2Session::HandleHeadersFrame(const nghttp2_frame* frame) {
  Isolate* isolate = env()->isolate();
  HandleScope scope(isolate);
  Local<Context> context = env()->context();
  Context::Scope context_scope(context);

  int32_t id = GetFrameID(frame);
  Debug(this, "handle headers frame for stream %d", id);
  Http2Stream* stream = FindStream(id);


  if (stream->IsDestroyed())
    return;

  std::vector<nghttp2_header> headers(stream->move_headers());
  DecrementCurrentSessionMemory(stream->current_headers_length_);
  stream->current_headers_length_ = 0;

  Local<String> name_str;
  Local<String> value_str;

  Local<Array> holder = Array::New(isolate);
  Local<Function> fn = env()->push_values_to_array_function();
  Local<Value> argv[NODE_PUSH_VAL_TO_ARRAY_MAX * 2];


  size_t n = 0;
  while (n < headers.size()) {
    size_t j = 0;
    while (n < headers.size() && j < arraysize(argv) / 2) {
      nghttp2_header item = headers[n++];

      name_str =
          ExternalHeader::New<true>(this, item.name).ToLocalChecked();
      value_str =
          ExternalHeader::New<false>(this, item.value).ToLocalChecked();
      argv[j * 2] = name_str;
      argv[j * 2 + 1] = value_str;
      j++;
    }


    if (j > 0) {
      fn->Call(env()->context(), holder, j * 2, argv).ToLocalChecked();
    }
  }

  Local<Value> args[5] = {
    stream->object(),
    Integer::New(isolate, id),
    Integer::New(isolate, stream->headers_category()),
    Integer::New(isolate, frame->hd.flags),
    holder
  };
  MakeCallback(env()->onheaders_string(), arraysize(args), args);
}

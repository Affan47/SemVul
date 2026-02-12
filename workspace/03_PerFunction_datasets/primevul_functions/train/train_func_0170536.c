void Http2Session::Ping(const FunctionCallbackInfo<Value>& args) {
  Environment* env = Environment::GetCurrent(args);
  Http2Session* session;
  ASSIGN_OR_RETURN_UNWRAP(&session, args.Holder());


  uint8_t* payload = nullptr;
  if (Buffer::HasInstance(args[0])) {
    payload = reinterpret_cast<uint8_t*>(Buffer::Data(args[0]));
    CHECK_EQ(Buffer::Length(args[0]), 8);
  }

  Local<Object> obj;
  if (!env->http2ping_constructor_template()
           ->NewInstance(env->context())
           .ToLocal(&obj)) {
    return;
  }
  if (obj->Set(env->context(), env->ondone_string(), args[1]).IsNothing())
    return;
  Http2Session::Http2Ping* ping = new Http2Ping(session, obj);


  if (!session->AddPing(ping)) {
    ping->Done(false);
    return args.GetReturnValue().Set(false);
  }


  ping->Send(payload);
  args.GetReturnValue().Set(true);
}

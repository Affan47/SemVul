void PackSettings(const FunctionCallbackInfo<Value>& args) {
  Environment* env = Environment::GetCurrent(args);

  Local<Object> obj;
  if (!env->http2settings_constructor_template()
           ->NewInstance(env->context())
           .ToLocal(&obj)) {
    return;
  }
  Http2Session::Http2Settings settings(env, nullptr, obj);
  args.GetReturnValue().Set(settings.Pack());
}

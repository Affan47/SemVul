void JSStream::New(const FunctionCallbackInfo<Value>& args) {


  CHECK(args.IsConstructCall());
  Environment* env = Environment::GetCurrent(args);
  new JSStream(env, args.This());
}

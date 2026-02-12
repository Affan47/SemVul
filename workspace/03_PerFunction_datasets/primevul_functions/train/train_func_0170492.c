void StreamBase::GetBytesWritten(const FunctionCallbackInfo<Value>& args) {
  Base* handle;
  ASSIGN_OR_RETURN_UNWRAP(&handle,
                          args.This(),
                          args.GetReturnValue().Set(0));

  StreamBase* wrap = static_cast<StreamBase*>(handle);

  args.GetReturnValue().Set(static_cast<double>(wrap->bytes_written_));
}

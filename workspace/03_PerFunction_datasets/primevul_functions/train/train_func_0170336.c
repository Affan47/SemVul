void TLSWrap::DestroySSL(const FunctionCallbackInfo<Value>& args) {
  TLSWrap* wrap;
  ASSIGN_OR_RETURN_UNWRAP(&wrap, args.Holder());
  Debug(wrap, "DestroySSL()");


  wrap->write_callback_scheduled_ = true;


  wrap->InvokeQueued(UV_ECANCELED, "Canceled because of SSL destruction");


  wrap->SSLWrap<TLSWrap>::DestroySSL();
  wrap->enc_in_ = nullptr;
  wrap->enc_out_ = nullptr;

  if (wrap->stream_ != nullptr)
    wrap->stream_->RemoveStreamListener(wrap);
  Debug(wrap, "DestroySSL() finished");
}

IntegerValue() const {
  i::Handle<i::Object> obj = Utils::OpenHandle(this);
  i::Handle<i::Object> num;
  if (obj->IsNumber()) {
    num = obj;
  } else {
    i::Isolate* isolate = i::Isolate::Current();
    if (IsDeadCheck(isolate, "v8::Value::IntegerValue()")) return 0;
    LOG_API(isolate, "IntegerValue");
    ENTER_V8(isolate);
    EXCEPTION_PREAMBLE(isolate);
    num = i::Execution::ToInteger(obj, &has_pending_exception);
    EXCEPTION_BAILOUT_CHECK(isolate, 0);
  }
  if (num->IsSmi()) {
    return i::Smi::cast(*num)->value();
  } else {
    return static_cast<int64_t>(num->Number());
  }
}

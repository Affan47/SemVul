Get(v8::Handle<Value> key) {
  ON_BAILOUT("v8::Object::Get()", return Local<v8::Value>());
  ENTER_V8;
  i::Handle<i::Object> self = Utils::OpenHandle(this);
  i::Handle<i::Object> key_obj = Utils::OpenHandle(*key);
  EXCEPTION_PREAMBLE();
  i::Handle<i::Object> result = i::GetProperty(self, key_obj);
  has_pending_exception = result.is_null();
  EXCEPTION_BAILOUT_CHECK(Local<Value>());
  return Utils::ToLocal(result);
}

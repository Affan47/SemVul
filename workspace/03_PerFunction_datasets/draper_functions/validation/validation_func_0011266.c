Dispose() {
  i::Isolate* isolate = i::Isolate::Current();
  if (!ApiCheck(isolate != NULL && isolate->IsDefaultIsolate(),
                "v8::V8::Dispose()",
                "Use v8::Isolate::Dispose() for a non-default isolate.")) {
    return false;
  }
  i::V8::TearDown();
  return true;
}

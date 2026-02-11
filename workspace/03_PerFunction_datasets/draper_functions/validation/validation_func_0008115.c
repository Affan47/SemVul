EnsureInitialized(const char* location) {
  if (i::V8::IsRunning()) {
    return true;
  }
  if (IsDeadCheck(location)) {
    return false;
  }
  return ApiCheck(v8::V8::Initialize(), location, "Error initializing V8");
}

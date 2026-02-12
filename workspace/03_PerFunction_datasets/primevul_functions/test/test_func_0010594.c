void ciEnv::record_failure(const char* reason) {
  if (_failure_reason == NULL) {

    _failure_reason = reason;
  }
}

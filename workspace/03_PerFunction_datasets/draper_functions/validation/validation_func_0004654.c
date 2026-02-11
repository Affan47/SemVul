RestoreStackGuard(char* from) {
  ExecutionAccess access(isolate_);
  memcpy(reinterpret_cast<char*>(&thread_local_), from, sizeof(ThreadLocal));
  isolate_->heap()->SetStackLimits();
  return from + sizeof(ThreadLocal);
}

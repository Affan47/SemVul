int enc_untrusted_utime(const char *filename, const struct utimbuf *times) {
  struct kLinux_utimbuf klinux_times {};


  TokLinuxutimbuf(times, &klinux_times);
  return EnsureInitializedAndDispatchSyscall(asylo::system_call::kSYS_utime,
                                             filename, &klinux_times);
}

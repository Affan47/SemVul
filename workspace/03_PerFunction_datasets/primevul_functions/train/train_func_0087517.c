int enc_untrusted_wait(int *wstatus) {
  int klinux_wstatus;
  pid_t ret = EnsureInitializedAndDispatchSyscall(
      asylo::system_call::kSYS_wait4, -1, &klinux_wstatus,
      0,
      nullptr);
  *wstatus = FromkLinuxToNewlibWstatus(klinux_wstatus);
  return ret;
}

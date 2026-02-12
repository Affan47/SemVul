int DeliverSignal(int linux_signum, int linux_sigcode) {
  absl::optional<int> signum = FromkLinuxSignalNumber(linux_signum);
  if (!signum) {
    return 1;
  }
  siginfo_t info;
  info.si_signo = *signum;
  info.si_code = linux_sigcode;
  SignalManager *signal_manager = SignalManager::GetInstance();
  const sigset_t mask = signal_manager->GetSignalMask();


  if (sigismember(&mask, *signum)) {
    return -1;
  }
  signal_manager->HandleSignal(*signum, &info, nullptr);
  return 0;
}

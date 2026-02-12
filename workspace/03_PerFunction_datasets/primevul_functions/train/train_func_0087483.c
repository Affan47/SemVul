int enc_untrusted_epoll_wait(int epfd, struct epoll_event *events,
                             int maxevents, int timeout) {
  if (maxevents <= 0) {
    errno = EINVAL;
    return -1;
  }
  auto klinux_events =
      absl::make_unique<struct klinux_epoll_event[]>(maxevents);

  int result = EnsureInitializedAndDispatchSyscall(
      asylo::system_call::kSYS_epoll_wait, epfd, klinux_events.get(), maxevents,
      timeout);


  if (result == -1) {


    return result;
  }
  if (result > maxevents) {
    TrustedPrimitives::BestEffortAbort(
        "enc_untrusted_epoll_wait: result found to be greater than maxevents "
        "supplied.");
  }

  for (int i = 0; i < result; i++) {
    if (!FromkLinuxEpollEvent(&klinux_events.get()[i], &events[i])) {
      errno = EBADE;
      return -1;
    }
  }
  return result;
}

int enc_untrusted_isatty(int fd) {
  MessageWriter input;
  input.Push(fd);
  MessageReader output;
  const auto status = NonSystemCallDispatcher(
      ::asylo::host_call::kIsAttyHandler, &input, &output);
  CheckStatusAndParamCount(status, output, "enc_untrusted_isatty", 2);

  int result = output.next<int>();


  if (result == 0) {
    int klinux_errno = output.next<int>();
    errno = FromkLinuxErrorNumber(klinux_errno);
  }
  return result;
}

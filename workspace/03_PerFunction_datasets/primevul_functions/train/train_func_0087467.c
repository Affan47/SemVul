struct passwd *enc_untrusted_getpwuid(uid_t uid) {
  MessageWriter input;
  MessageReader output;
  input.Push<uid_t>(uid);
  const auto status = NonSystemCallDispatcher(
      ::asylo::host_call::kGetPwUidHandler, &input, &output);
  CheckStatusAndParamCount(status, output, "enc_untrusted_getpwuid", 1,
                           false);

  int klinux_errno = output.next<int>();
  if (output.size() == 1) {
    errno = FromkLinuxErrorNumber(klinux_errno);
    return nullptr;
  }


  static struct passwd_holder passwd_buffers;
  if (!DeserializePasswd(&output, &passwd_buffers) ||
      !PasswdHolderToPasswd(&passwd_buffers, &global_passwd)) {
    errno = EFAULT;
    return nullptr;
  }

  return &global_passwd;
}

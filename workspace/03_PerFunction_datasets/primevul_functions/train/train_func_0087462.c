int enc_untrusted_clock_getcpuclockid(pid_t pid, clockid_t *clock_id) {
  MessageWriter input;
  input.Push<uint32_t>(pid);
  MessageReader output;
  asylo::primitives::PrimitiveStatus status =
      asylo::host_call::NonSystemCallDispatcher(
          asylo::host_call::kGetCpuClockIdHandler, &input, &output);
  CheckStatusAndParamCount(status, output, "enc_untrusted_getcpuclockid", 2);


  int klinux_errno_result = output.next<int32_t>();
  if (klinux_errno_result != 0) {
    return FromkLinuxErrorNumber(klinux_errno_result);
  }

  clockid_t klinux_clk_id = output.next<uint64_t>();
  *clock_id = FromkLinuxClockId(klinux_clk_id);
  return 0;
}

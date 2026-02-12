restart_timeout(NCR_Instance inst, double delay)
{

  if (inst->tx_suspended) {
    assert(!inst->timer_running);
    return;
  }


  if (inst->timer_running)
    SCH_RemoveTimeout(inst->timeout_id);


  inst->timeout_id = SCH_AddTimeoutInClass(delay, SAMPLING_SEPARATION,
                                           SAMPLING_RANDOMNESS,
                                           SCH_NtpSamplingClass,
                                           transmit_timeout, (void *)inst);
  inst->timer_running = 1;
}

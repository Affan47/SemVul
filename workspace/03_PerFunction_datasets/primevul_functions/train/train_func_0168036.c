get_transmit_delay(NCR_Instance inst, int on_tx, double last_tx)
{
  int poll_to_use, stratum_diff;
  double delay_time;


  switch (inst->opmode) {
    case MD_OFFLINE:
      assert(0);
      break;
    case MD_ONLINE:


      switch(inst->mode) {
        case MODE_CLIENT:


          poll_to_use = inst->local_poll;

          delay_time = (double) (1UL<<poll_to_use);

          break;

        case MODE_ACTIVE:


          poll_to_use = inst->local_poll;
          if (poll_to_use > inst->remote_poll)
            poll_to_use = inst->remote_poll;
          if (poll_to_use < inst->minpoll)
            poll_to_use = inst->minpoll;

          delay_time = (double) (1UL<<poll_to_use);


          stratum_diff = inst->remote_stratum - REF_GetOurStratum();
          if ((stratum_diff > 0 && last_tx * PEER_SAMPLING_ADJ < delay_time) ||
              (!on_tx && !stratum_diff &&
               last_tx / delay_time > PEER_SAMPLING_ADJ - 0.5))
            delay_time *= PEER_SAMPLING_ADJ;


          if (last_tx > 0.0)
            delay_time -= last_tx;
          if (delay_time < 0.0)
            delay_time = 0.0;

          break;
        default:
          assert(0);
          break;
      }
      break;

    case MD_BURST_WAS_ONLINE:
    case MD_BURST_WAS_OFFLINE:

      delay_time = on_tx ? BURST_TIMEOUT : BURST_INTERVAL;
      break;
    default:
      assert(0);
      break;
  }

  return delay_time;
}

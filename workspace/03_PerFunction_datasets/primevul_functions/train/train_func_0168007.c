receive_packet(NTP_Packet *message, struct timeval *now, double now_err, NCR_Instance inst, NTP_Local_Address *local_addr, int length)
{
  int pkt_leap;
  uint32_t pkt_refid, pkt_key_id;
  double pkt_root_delay;
  double pkt_root_dispersion;


  struct timeval sample_time;


  double offset;


  double delay, dispersion, distance;


  double root_delay, root_dispersion;


  double skew, source_freq_lo, source_freq_hi;


  struct timeval remote_receive_tv, remote_transmit_tv;
  struct timeval remote_reference_tv;
  struct timeval local_average, remote_average;
  double local_interval, remote_interval;


  int test1, test2, test3, test5, test6, test7;
  int valid_packet;


  int testA, testB, testC, testD;
  int good_packet;


  int kod_rate;


  static const char sync_stats[4] = {'N', '+', '-', '?'};


  double estimated_offset;


  double error_in_estimate;

  double delay_time, precision;
  int requeue_transmit;


  pkt_leap = NTP_LVM_TO_LEAP(message->lvm);
  pkt_refid = ntohl(message->reference_id);
  pkt_root_delay = UTI_Int32ToDouble(message->root_delay);
  pkt_root_dispersion = UTI_Int32ToDouble(message->root_dispersion);

  UTI_Int64ToTimeval(&message->receive_ts, &remote_receive_tv);
  UTI_Int64ToTimeval(&message->transmit_ts, &remote_transmit_tv);
  UTI_Int64ToTimeval(&message->reference_ts, &remote_reference_tv);


  test1 = message->transmit_ts.hi != inst->remote_orig.hi ||
          message->transmit_ts.lo != inst->remote_orig.lo;


  test2 = message->originate_ts.hi == inst->local_ntp_tx.hi &&
          message->originate_ts.lo == inst->local_ntp_tx.lo;


  test3 = (message->originate_ts.hi || message->originate_ts.lo) &&
          (message->receive_ts.hi || message->receive_ts.lo) &&
          (message->reference_ts.hi || message->reference_ts.lo) &&
          (message->transmit_ts.hi || message->transmit_ts.lo);


  test5 = !inst->do_auth ||
          (check_packet_auth(message, length, NULL, &pkt_key_id) &&
           pkt_key_id == inst->auth_key_id);


  test6 = pkt_leap != LEAP_Unsynchronised &&
          message->stratum < NTP_MAX_STRATUM &&
          message->stratum != NTP_INVALID_STRATUM;


  test7 = pkt_root_delay / 2.0 + pkt_root_dispersion < NTP_MAX_DISPERSION &&
          UTI_CompareTimevals(&remote_reference_tv, &remote_transmit_tv) < 1;


  valid_packet = test1 && test2 && test3 && test5 && test6 && test7;


  kod_rate = 0;
  if (test1 && test2 && test5 && pkt_leap == LEAP_Unsynchronised &&
      message->stratum == NTP_INVALID_STRATUM) {
    if (pkt_refid == KOD_RATE)
      kod_rate = 1;
  }


  if (test5) {
    inst->remote_orig = message->transmit_ts;
    inst->local_rx = *now;
  }


  if (test2)
    inst->local_ntp_tx.hi = inst->local_ntp_tx.lo = 0;

  if (valid_packet) {
    precision = LCL_GetSysPrecisionAsQuantum() +
                UTI_Log2ToDouble(message->precision);

    SRC_GetFrequencyRange(inst->source, &source_freq_lo, &source_freq_hi);

    UTI_AverageDiffTimevals(&remote_receive_tv, &remote_transmit_tv,
                            &remote_average, &remote_interval);

    UTI_AverageDiffTimevals(&inst->local_tx, now,
                            &local_average, &local_interval);


    delay = local_interval - remote_interval * (1.0 + source_freq_lo);


    delay = fabs(delay);
    if (delay < precision)
      delay = precision;


    UTI_DiffTimevalsToDouble(&offset, &remote_average, &local_average);


    sample_time = local_average;


    skew = (source_freq_hi - source_freq_lo) / 2.0;


    dispersion = precision + now_err + skew * fabs(local_interval);


    testA = delay <= inst->max_delay;


    testB = inst->max_delay_ratio <= 1.0 ||
            delay / SRC_MinRoundTripDelay(inst->source) <= inst->max_delay_ratio;


    testC = SRC_IsGoodSample(inst->source, -offset, delay,
                             inst->max_delay_dev_ratio, LCL_GetMaxClockError(),
                             &sample_time);


    testD = message->stratum <= 1 || pkt_refid != UTI_IPToRefid(&local_addr->ip_addr);
  } else {
    offset = delay = dispersion = 0.0;
    sample_time = *now;
    testA = testB = testC = testD = 0;
  }


  good_packet = testA && testB && testC && testD;

  root_delay = pkt_root_delay + delay;
  root_dispersion = pkt_root_dispersion + dispersion;
  distance = dispersion + 0.5 * delay;

  DEBUG_LOG(LOGF_NtpCore, "NTP packet lvm=%o stratum=%d poll=%d prec=%d root_delay=%f root_disp=%f refid=%"PRIx32" [%s]",
            message->lvm, message->stratum, message->poll, message->precision,
            pkt_root_delay, pkt_root_dispersion, pkt_refid,
            message->stratum == NTP_INVALID_STRATUM ? UTI_RefidToString(pkt_refid) : "");
  DEBUG_LOG(LOGF_NtpCore, "reference=%s origin=%s receive=%s transmit=%s",
            UTI_TimestampToString(&message->reference_ts),
            UTI_TimestampToString(&message->originate_ts),
            UTI_TimestampToString(&message->receive_ts),
            UTI_TimestampToString(&message->transmit_ts));
  DEBUG_LOG(LOGF_NtpCore, "offset=%f delay=%f dispersion=%f root_delay=%f root_dispersion=%f",
            offset, delay, dispersion, root_delay, root_dispersion);
  DEBUG_LOG(LOGF_NtpCore, "test123=%d%d%d test567=%d%d%d testABCD=%d%d%d%d kod_rate=%d valid=%d good=%d",
            test1, test2, test3, test5, test6, test7, testA, testB, testC, testD,
            kod_rate, valid_packet, good_packet);

  requeue_transmit = 0;


  if (kod_rate) {
    if (message->poll > inst->minpoll) {

      if (message->poll <= MAX_KOD_RATE_POLL)
        inst->minpoll = message->poll;
      else if (inst->minpoll < MAX_KOD_RATE_POLL)
        inst->minpoll = MAX_KOD_RATE_POLL;

      if (inst->minpoll > inst->maxpoll)
        inst->maxpoll = inst->minpoll;
      if (inst->minpoll > inst->local_poll)
        inst->local_poll = inst->minpoll;

      LOG(LOGS_WARN, LOGF_NtpCore,
          "Received KoD RATE with poll %d from %s, minpoll set to %d",
          message->poll, UTI_IPToString(&inst->remote_addr.ip_addr),
          inst->minpoll);
    }


    if (inst->opmode == MD_BURST_WAS_OFFLINE || inst->opmode == MD_BURST_WAS_ONLINE) {
      inst->burst_good_samples_to_go = 0;
      LOG(LOGS_WARN, LOGF_NtpCore, "Received KoD RATE from %s, burst sampling stopped",
          UTI_IPToString(&inst->remote_addr.ip_addr));
    }

    requeue_transmit = 1;
  }

  if (valid_packet) {
    inst->remote_poll = message->poll;
    inst->remote_stratum = message->stratum;
    inst->tx_count = 0;
    SRC_UpdateReachability(inst->source, 1);

    if (good_packet) {

      estimated_offset = SRC_PredictOffset(inst->source, &sample_time);

      SRC_AccumulateSample(inst->source,
                           &sample_time,
                           offset, delay, dispersion,
                           root_delay, root_dispersion,
                           message->stratum > inst->min_stratum ?
                             message->stratum : inst->min_stratum,
                           (NTP_Leap) pkt_leap);

      SRC_SelectSource(inst->source);


      error_in_estimate = fabs(-offset - estimated_offset);


      adjust_poll(inst, get_poll_adj(inst, error_in_estimate, distance));


      switch (inst->opmode) {
        case MD_BURST_WAS_ONLINE:
        case MD_BURST_WAS_OFFLINE:
          --inst->burst_good_samples_to_go;
          if (inst->burst_good_samples_to_go <= 0) {
            if (inst->opmode == MD_BURST_WAS_ONLINE)
              inst->opmode = MD_ONLINE;
            else
              take_offline(inst);
          }
          break;
        default:
          break;
      }
    } else {

      adjust_poll(inst, 0.1);
    }


    close_client_socket(inst);

    requeue_transmit = 1;
  }


  if (requeue_transmit && inst->opmode != MD_OFFLINE) {
    delay_time = get_transmit_delay(inst, 0, local_interval);

    if (kod_rate) {

      delay_time += (double) (4 * (1UL << inst->minpoll));
    }


    assert(inst->timer_running);
    restart_timeout(inst, delay_time);
  }


  if (logfileid != -1) {
    LOG_FileWrite(logfileid, "%s %-15s %1c %2d %1d%1d%1d %1d%1d%1d %1d%1d%1d%d  %2d %2d %4.2f %10.3e %10.3e %10.3e %10.3e %10.3e",
            UTI_TimeToLogForm(sample_time.tv_sec),
            UTI_IPToString(&inst->remote_addr.ip_addr),
            sync_stats[pkt_leap],
            message->stratum,
            test1, test2, test3, test5, test6, test7, testA, testB, testC, testD,
            inst->local_poll, inst->remote_poll,
            inst->poll_score,
            offset, delay, dispersion,
            pkt_root_delay, pkt_root_dispersion);
  }

  return valid_packet;
}

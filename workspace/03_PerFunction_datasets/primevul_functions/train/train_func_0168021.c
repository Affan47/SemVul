transmit_packet(NTP_Mode my_mode,
                int my_poll,
                int version,
                int do_auth,
                uint32_t key_id,
                NTP_int64 *orig_ts,
                struct timeval *local_rx,
                struct timeval *local_tx,


                NTP_int64 *local_ntp_tx,


                NTP_Remote_Address *where_to,
                NTP_Local_Address *from
                )
{
  NTP_Packet message;
  int leap, auth_len, length, ret;
  struct timeval local_receive, local_transmit;


  int are_we_synchronised, our_stratum, smooth_time;
  NTP_Leap leap_status;
  uint32_t our_ref_id, ts_fuzz;
  struct timeval our_ref_time;
  double our_root_delay, our_root_dispersion, smooth_offset;


  if (version > NTP_VERSION) {
    version = NTP_VERSION;
  }


  SCH_GetLastEventTime(&local_transmit, NULL, NULL);

  REF_GetReferenceParams(&local_transmit,
                         &are_we_synchronised, &leap_status,
                         &our_stratum,
                         &our_ref_id, &our_ref_time,
                         &our_root_delay, &our_root_dispersion);


  if (SMT_IsEnabled() && (my_mode == MODE_SERVER || my_mode == MODE_BROADCAST)) {
    smooth_offset = SMT_GetOffset(&local_transmit);
    smooth_time = fabs(smooth_offset) > LCL_GetSysPrecisionAsQuantum();


    if (REF_GetLeapMode() == REF_LeapModeSlew &&
        (leap_status == LEAP_InsertSecond || leap_status == LEAP_DeleteSecond))
      leap_status = LEAP_Normal;
  } else {
    smooth_time = 0;
    smooth_offset = 0.0;
  }

  if (smooth_time) {
    our_ref_id = NTP_REFID_SMOOTH;
    UTI_AddDoubleToTimeval(&our_ref_time, smooth_offset, &our_ref_time);
    UTI_AddDoubleToTimeval(local_rx, smooth_offset, &local_receive);
  } else {
    local_receive = *local_rx;
  }

  if (are_we_synchronised) {
    leap = (int) leap_status;
  } else {
    leap = LEAP_Unsynchronised;
  }


  message.lvm = NTP_LVM(leap, version, my_mode);

  if (our_stratum < NTP_MAX_STRATUM) {
    message.stratum = our_stratum;
  } else {
    message.stratum = NTP_INVALID_STRATUM;
  }

  message.poll = my_poll;
  message.precision = LCL_GetSysPrecisionAsLog();


  message.root_delay = UTI_DoubleToInt32(our_root_delay);
  message.root_dispersion = UTI_DoubleToInt32(our_root_dispersion);

  message.reference_id = htonl(our_ref_id);


  UTI_TimevalToInt64(&our_ref_time, &message.reference_ts, 0);


  message.originate_ts = *orig_ts;


  UTI_TimevalToInt64(&local_receive, &message.receive_ts, 0);


  ts_fuzz = UTI_GetNTPTsFuzz(message.precision);


  LCL_ReadCookedTime(&local_transmit, NULL);

  if (smooth_time)
    UTI_AddDoubleToTimeval(&local_transmit, smooth_offset, &local_transmit);

  length = NTP_NORMAL_PACKET_LENGTH;


  if (do_auth && key_id) {


    local_transmit.tv_usec += KEY_GetAuthDelay(key_id);
    UTI_NormaliseTimeval(&local_transmit);
    UTI_TimevalToInt64(&local_transmit, &message.transmit_ts, ts_fuzz);

    auth_len = KEY_GenerateAuth(key_id, (unsigned char *) &message,
        offsetof(NTP_Packet, auth_keyid),
        (unsigned char *)&message.auth_data, sizeof (message.auth_data));
    if (auth_len > 0) {
      message.auth_keyid = htonl(key_id);
      length += sizeof (message.auth_keyid) + auth_len;
    } else {
      DEBUG_LOG(LOGF_NtpCore,
                "Could not generate auth data with key %"PRIu32" to send packet",
                key_id);
      return 0;
    }
  } else {
    if (do_auth) {

      message.auth_keyid = 0;
      length += sizeof (message.auth_keyid);
    }
    UTI_TimevalToInt64(&local_transmit, &message.transmit_ts, ts_fuzz);
  }

  ret = NIO_SendPacket(&message, where_to, from, length);

  if (local_tx) {
    *local_tx = local_transmit;
  }

  if (local_ntp_tx) {
    *local_ntp_tx = message.transmit_ts;
  }

  return ret;
}

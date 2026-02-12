NCR_ProcessUnknown
(NTP_Packet *message,
 struct timeval *now,
 double now_err,
 NTP_Remote_Address *remote_addr,
 NTP_Local_Address *local_addr,
 int length
 )
{
  NTP_Mode pkt_mode, my_mode;
  int has_auth, valid_auth;
  uint32_t key_id;


  if (!NIO_IsServerSocket(local_addr->sock_fd)) {
    DEBUG_LOG(LOGF_NtpCore, "NTP request packet received by client socket %d",
              local_addr->sock_fd);
    return;
  }

  if (!check_packet_format(message, length))
    return;

  if (!ADF_IsAllowed(access_auth_table, &remote_addr->ip_addr)) {
    DEBUG_LOG(LOGF_NtpCore, "NTP packet received from unauthorised host %s port %d",
              UTI_IPToString(&remote_addr->ip_addr),
              remote_addr->port);
    return;
  }

  pkt_mode = NTP_LVM_TO_MODE(message->lvm);

  switch (pkt_mode) {
    case MODE_ACTIVE:

      my_mode = MODE_PASSIVE;
      CLG_LogNTPPeerAccess(&remote_addr->ip_addr, now->tv_sec);
      break;
    case MODE_CLIENT:

      my_mode = MODE_SERVER;
      CLG_LogNTPClientAccess(&remote_addr->ip_addr, now->tv_sec);
      break;
    default:

      DEBUG_LOG(LOGF_NtpCore, "NTP packet discarded pkt_mode=%d", pkt_mode);
      return;
  }


  valid_auth = check_packet_auth(message, length, &has_auth, &key_id);


  if (!valid_auth)
    key_id = 0;


  transmit_packet(my_mode, message->poll, NTP_LVM_TO_VERSION(message->lvm),
                  has_auth, key_id, &message->transmit_ts, now, NULL, NULL,
                  remote_addr, local_addr);
}

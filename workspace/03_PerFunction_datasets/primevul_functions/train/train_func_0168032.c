NCR_ProcessKnown
(NTP_Packet *message,
 struct timeval *now,
 double now_err,
 NCR_Instance inst,
 NTP_Local_Address *local_addr,
 int length
 )
{
  int pkt_mode, proc_packet, proc_as_unknown, log_peer_access;

  if (!check_packet_format(message, length))
    return 0;

  pkt_mode = NTP_LVM_TO_MODE(message->lvm);
  proc_packet = 0;
  proc_as_unknown = 0;
  log_peer_access = 0;


  switch (pkt_mode) {
    case MODE_ACTIVE:
      switch (inst->mode) {
        case MODE_ACTIVE:

          log_peer_access = 1;
          proc_packet = 1;
          break;
        case MODE_PASSIVE:


          break;
        case MODE_CLIENT:


          proc_as_unknown = 1;
          break;
        default:

          break;
      }
      break;

    case MODE_PASSIVE:
      switch (inst->mode) {
        case MODE_ACTIVE:


          log_peer_access = 1;
          proc_packet = 1;
          break;
        case MODE_PASSIVE:

          break;
        default:

          break;
      }
      break;

    case MODE_CLIENT:


      proc_as_unknown = 1;
      break;

    case MODE_SERVER:

      if (inst->presend_done)
        break;

      switch (inst->mode) {
        case MODE_CLIENT:

          proc_packet = 1;
          break;
        default:

          break;
      }
      break;

    case MODE_BROADCAST:

      break;

    default:

      break;
  }

  if (log_peer_access)
    CLG_LogNTPPeerAccess(&inst->remote_addr.ip_addr, now->tv_sec);

  if (proc_packet) {

    if (local_addr->sock_fd != inst->local_addr.sock_fd) {
      DEBUG_LOG(LOGF_NtpCore,
                "Packet received by wrong socket %d (expected %d)",
                local_addr->sock_fd, inst->local_addr.sock_fd);
      return 0;
    }


    if (inst->opmode == MD_OFFLINE || inst->tx_suspended) {
      DEBUG_LOG(LOGF_NtpCore, "Packet from offline source");
      return 0;
    }

    return receive_packet(message, now, now_err, inst, local_addr, length);
  } else if (proc_as_unknown) {
    NCR_ProcessUnknown(message, now, now_err, &inst->remote_addr,
                       local_addr, length);

    return 0;
  } else {
    DEBUG_LOG(LOGF_NtpCore, "NTP packet discarded pkt_mode=%d our_mode=%d",
              pkt_mode, inst->mode);
    return 0;
  }
}

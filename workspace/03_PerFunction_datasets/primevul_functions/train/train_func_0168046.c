transmit_timeout(void *arg)
{
  NCR_Instance inst = (NCR_Instance) arg;
  int sent;

  inst->timer_running = 0;

  switch (inst->opmode) {
    case MD_BURST_WAS_ONLINE:

      if (inst->burst_total_samples_to_go <= 1)
        inst->opmode = MD_ONLINE;
    case MD_BURST_WAS_OFFLINE:
      if (inst->burst_total_samples_to_go <= 0)
        take_offline(inst);
      break;
    default:
      break;
  }


  if (inst->auto_offline && inst->tx_count >= 2)
    NCR_TakeSourceOffline(inst);

  if (inst->opmode == MD_OFFLINE) {
    return;
  }

  DEBUG_LOG(LOGF_NtpCore, "Transmit timeout for [%s:%d]",
      UTI_IPToString(&inst->remote_addr.ip_addr), inst->remote_addr.port);


  if (inst->mode == MODE_CLIENT) {
    close_client_socket(inst);
    assert(inst->local_addr.sock_fd == INVALID_SOCK_FD);
    inst->local_addr.sock_fd = NIO_OpenClientSocket(&inst->remote_addr);
  }


  if ((inst->presend_minpoll > 0) &&
      (inst->presend_minpoll <= inst->local_poll) &&
      !inst->presend_done) {


    transmit_packet(MODE_CLIENT, inst->local_poll, inst->version, 0, 0,
                    &inst->remote_orig, &inst->local_rx, NULL, NULL,
                    &inst->remote_addr, &inst->local_addr);

    inst->presend_done = 1;


    restart_timeout(inst, WARM_UP_DELAY);

    return;
  }

  inst->presend_done = 0;

  sent = transmit_packet(inst->mode, inst->local_poll,
                         inst->version,
                         inst->do_auth, inst->auth_key_id,
                         &inst->remote_orig,
                         &inst->local_rx, &inst->local_tx, &inst->local_ntp_tx,
                         &inst->remote_addr,
                         &inst->local_addr);

  ++inst->tx_count;


  if (inst->tx_count >= 2) {


    if (sent) {
      adjust_poll(inst, SRC_IsSyncPeer(inst->source) ? 0.1 : 0.25);
    }

    SRC_UpdateReachability(inst->source, 0);
  }

  switch (inst->opmode) {
    case MD_BURST_WAS_ONLINE:

      if (!sent && !SRC_IsReachable(inst->source))
        break;

    case MD_BURST_WAS_OFFLINE:
      --inst->burst_total_samples_to_go;
      break;
    default:
      break;
  }


  restart_timeout(inst, get_transmit_delay(inst, 1, 0.0));
}

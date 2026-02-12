void ProtocolV1::session_reset() {
  ldout(cct, 10) << __func__ << " started" << dendl;

  std::lock_guard<std::mutex> l(connection->write_lock);
  if (connection->delay_state) {
    connection->delay_state->discard();
  }

  connection->dispatch_queue->discard_queue(connection->conn_id);
  discard_out_queue();


  connection->dispatch_queue->queue_remote_reset(connection);

  randomize_out_seq();

  in_seq = 0;
  connect_seq = 0;

  ack_left = 0;
  once_ready = false;
  can_write = WriteStatus::NOWRITE;
}

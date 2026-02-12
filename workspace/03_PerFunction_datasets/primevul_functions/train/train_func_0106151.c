CtPtr ProtocolV1::replace(AsyncConnectionRef existing,
                          ceph_msg_connect_reply &reply,
                          bufferlist &authorizer_reply) {
  ldout(cct, 10) << __func__ << " accept replacing " << existing << dendl;

  connection->inject_delay();
  if (existing->policy.lossy) {

    ldout(cct, 1) << __func__ << " replacing on lossy channel, failing existing"
                  << dendl;
    existing->protocol->stop();
    existing->dispatch_queue->queue_reset(existing.get());
  } else {
    ceph_assert(can_write == WriteStatus::NOWRITE);
    existing->write_lock.lock();

    ProtocolV1 *exproto = dynamic_cast<ProtocolV1 *>(existing->protocol.get());


    if (is_reset_from_peer) {
      exproto->is_reset_from_peer = true;
    }

    connection->center->delete_file_event(connection->cs.fd(),
                                          EVENT_READABLE | EVENT_WRITABLE);

    if (existing->delay_state) {
      existing->delay_state->flush();
      ceph_assert(!connection->delay_state);
    }
    exproto->reset_recv_state();

    exproto->connect_msg.features = connect_msg.features;

    auto temp_cs = std::move(connection->cs);
    EventCenter *new_center = connection->center;
    Worker *new_worker = connection->worker;


    stop();

    connection->dispatch_queue->queue_reset(connection);
    ldout(messenger->cct, 1)
        << __func__ << " stop myself to swap existing" << dendl;
    exproto->can_write = WriteStatus::REPLACING;
    exproto->replacing = true;
    exproto->write_in_progress = false;
    existing->state_offset = 0;

    exproto->state = NONE;
    existing->state = AsyncConnection::STATE_NONE;

    existing->recv_start = existing->recv_end = 0;

    ceph_assert(connection->recv_start == connection->recv_end);

    exproto->authorizer_challenge.reset();

    auto deactivate_existing = std::bind(
        [existing, new_worker, new_center, exproto, reply,
         authorizer_reply](ConnectedSocket &cs) mutable {

          {
            std::lock_guard<std::mutex> l(existing->lock);
            existing->write_lock.lock();
            exproto->requeue_sent();
            existing->outgoing_bl.clear();
            existing->open_write = false;
            existing->write_lock.unlock();
            if (exproto->state == NONE) {
              existing->shutdown_socket();
              existing->cs = std::move(cs);
              existing->worker->references--;
              new_worker->references++;
              existing->logger = new_worker->get_perf_counter();
              existing->worker = new_worker;
              existing->center = new_center;
              if (existing->delay_state)
                existing->delay_state->set_center(new_center);
            } else if (exproto->state == CLOSED) {
              auto back_to_close =
                  std::bind([](ConnectedSocket &cs) mutable { cs.close(); },
                            std::move(cs));
              new_center->submit_to(new_center->get_id(),
                                    std::move(back_to_close), true);
              return;
            } else {
              ceph_abort();
            }
          }


          auto transfer_existing = [existing, exproto, reply,
                                    authorizer_reply]() mutable {
            std::lock_guard<std::mutex> l(existing->lock);
            if (exproto->state == CLOSED) return;
            ceph_assert(exproto->state == NONE);


            ceph_assert(existing->last_tick_id == 0);

            existing->last_connect_started = ceph::coarse_mono_clock::now();
            existing->last_tick_id = existing->center->create_time_event(
              existing->connect_timeout_us, existing->tick_handler);
            existing->state = AsyncConnection::STATE_CONNECTION_ESTABLISHED;
            exproto->state = ACCEPTING;

            existing->center->create_file_event(
                existing->cs.fd(), EVENT_READABLE, existing->read_handler);
            reply.global_seq = exproto->peer_global_seq;
            exproto->run_continuation(exproto->send_connect_message_reply(
                CEPH_MSGR_TAG_RETRY_GLOBAL, reply, authorizer_reply));
          };
          if (existing->center->in_thread())
            transfer_existing();
          else
            existing->center->submit_to(existing->center->get_id(),
                                        std::move(transfer_existing), true);
        },
        std::move(temp_cs));

    existing->center->submit_to(existing->center->get_id(),
                                std::move(deactivate_existing), true);
    existing->write_lock.unlock();
    existing->lock.unlock();
    return nullptr;
  }
  existing->lock.unlock();

  return open(reply, authorizer_reply);
}

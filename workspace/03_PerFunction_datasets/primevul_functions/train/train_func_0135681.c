handle_hs_exit_conn(circuit_t *circ, edge_connection_t *conn)
{
  int ret;
  origin_circuit_t *origin_circ;

  assert_circuit_ok(circ);
  tor_assert(circ->purpose == CIRCUIT_PURPOSE_S_REND_JOINED);
  tor_assert(conn);

  log_debug(LD_REND, "Connecting the hidden service rendezvous circuit "
                     "to the service destination.");

  origin_circ = TO_ORIGIN_CIRCUIT(circ);
  conn->base_.address = tor_strdup("(rendezvous)");
  conn->base_.state = EXIT_CONN_STATE_CONNECTING;

  if (origin_circ->hs_ident) {

    conn->hs_ident =
      hs_ident_edge_conn_new(&origin_circ->hs_ident->identity_pk);
    tor_assert(connection_edge_is_rendezvous_stream(conn));
    ret = hs_service_set_conn_addr_port(origin_circ, conn);
  } else {

    tor_assert_nonfatal_unreached();
    return -1;
  }
  if (ret < 0) {
    log_info(LD_REND, "Didn't find rendezvous service at %s",
             connection_describe_peer(TO_CONN(conn)));


    relay_send_end_cell_from_edge(conn->stream_id, circ,
                                  END_STREAM_REASON_DONE,
                                  origin_circ->cpath->prev);
    connection_free_(TO_CONN(conn));


    if (ret < -1) {
      return END_CIRC_AT_ORIGIN;
    } else {
      return 0;
    }
  }


  conn->cpath_layer = origin_circ->cpath->prev;


  if (!origin_circ->p_streams)
    circpad_machine_event_circ_has_streams(origin_circ);


  conn->next_stream = origin_circ->p_streams;
  origin_circ->p_streams = conn;
  conn->on_circuit = circ;
  assert_circuit_ok(circ);

  hs_inc_rdv_stream_counter(origin_circ);


  if (conn->hs_ident) {
    hs_circuit_id_protocol_t circuit_id_protocol =
      hs_service_exports_circuit_id(&conn->hs_ident->identity_pk);
    export_hs_client_circuit_id(conn, circuit_id_protocol);
  }


  connection_exit_connect(conn);


  pathbias_mark_use_success(origin_circ);
  return 0;
}

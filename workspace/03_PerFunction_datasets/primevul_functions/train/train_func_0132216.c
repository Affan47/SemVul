connection_half_edge_add(const edge_connection_t *conn,
                         origin_circuit_t *circ)
{
  half_edge_t *half_conn = NULL;
  int insert_at = 0;
  int ignored;


  if (connection_half_edge_find_stream_id(circ->half_streams,
                                          conn->stream_id)) {
    log_warn(LD_BUG, "Duplicate stream close for stream %d on circuit %d",
             conn->stream_id, circ->global_identifier);
    return;
  }

  half_conn = tor_malloc_zero(sizeof(half_edge_t));
  ++n_half_conns_allocated;

  if (!circ->half_streams) {
    circ->half_streams = smartlist_new();
  }

  half_conn->stream_id = conn->stream_id;


  half_conn->sendmes_pending =
   (STREAMWINDOW_START-conn->package_window)/STREAMWINDOW_INCREMENT;


  half_conn->connected_pending = conn->base_.state ==
      AP_CONN_STATE_CONNECT_WAIT;


  if (conn->base_.state != AP_CONN_STATE_RESOLVE_WAIT) {

    half_conn->data_pending = conn->deliver_window;
  }

  insert_at = smartlist_bsearch_idx(circ->half_streams, &half_conn->stream_id,
                                    connection_half_edge_compare_bsearch,
                                    &ignored);
  smartlist_insert(circ->half_streams, insert_at, half_conn);
}

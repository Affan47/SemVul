circuit_clear_cell_queue(circuit_t *circ, or_connection_t *orconn)
{
  cell_queue_t *queue;
  if (circ->n_conn == orconn) {
    queue = &circ->n_conn_cells;
  } else {
    or_circuit_t *orcirc = TO_OR_CIRCUIT(circ);
    tor_assert(orcirc->p_conn == orconn);
    queue = &orcirc->p_conn_cells;
  }

  if (queue->n)
    make_circuit_inactive_on_conn(circ,orconn);

  cell_queue_clear(queue);
}

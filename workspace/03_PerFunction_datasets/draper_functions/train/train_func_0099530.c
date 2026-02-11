connection_link_connections(connection_t *conn_a, connection_t *conn_b)
{
  tor_assert(! SOCKET_OK(conn_a->s));
  tor_assert(! SOCKET_OK(conn_b->s));

  conn_a->linked = 1;
  conn_b->linked = 1;
  conn_a->linked_conn = conn_b;
  conn_b->linked_conn = conn_a;
}

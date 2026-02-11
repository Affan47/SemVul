ladish_graph_trick_dicts(ladish_graph_handle graph_handle)
{
  struct list_head * node_ptr;
  struct ladish_graph_connection * connection_ptr;
  struct ladish_graph_client * client_ptr;
  struct ladish_graph_port * port_ptr;

  list_for_each(node_ptr, &graph_ptr->connections)
  {
    connection_ptr = list_entry(node_ptr, struct ladish_graph_connection, siblings);
    if (!connection_ptr->hidden)
    {
      graph_ptr->graph_version++;
      ladish_graph_emit_ports_disconnected(graph_ptr, connection_ptr);
    }
  }

  list_for_each(node_ptr, &graph_ptr->ports)
  {
    port_ptr = list_entry(node_ptr, struct ladish_graph_port, siblings_graph);

    if (!port_ptr->hidden)
    {
      graph_ptr->graph_version++;
      ladish_graph_emit_port_disappeared(graph_ptr, port_ptr);
    }
  }

  list_for_each(node_ptr, &graph_ptr->clients)
  {
    client_ptr = list_entry(node_ptr, struct ladish_graph_client, siblings);

    if (!client_ptr->hidden)
    {
      graph_ptr->graph_version++;
      ladish_graph_emit_client_disappeared(graph_ptr, client_ptr);
      graph_ptr->graph_version++;
      ladish_graph_emit_client_appeared(graph_ptr, client_ptr);
    }
  }

  list_for_each(node_ptr, &graph_ptr->ports)
  {
    port_ptr = list_entry(node_ptr, struct ladish_graph_port, siblings_graph);

    if (!port_ptr->hidden)
    {
      graph_ptr->graph_version++;
      ladish_graph_emit_port_appeared(graph_ptr, port_ptr);
    }
  }

  list_for_each(node_ptr, &graph_ptr->connections)
  {
    connection_ptr = list_entry(node_ptr, struct ladish_graph_connection, siblings);
    if (!connection_ptr->hidden)
    {
      graph_ptr->graph_version++;
      ladish_graph_emit_ports_connected(graph_ptr, connection_ptr);
    }
  }
}

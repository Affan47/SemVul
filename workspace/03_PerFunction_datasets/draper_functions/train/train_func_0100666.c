flow_entry_compare(const flow_table_entry_t* const first,
                              const flow_table_entry_t* const second) {
  return first->ip_source == second->ip_source
      && first->ip_destination == second->ip_destination
      && first->transport_protocol == second->transport_protocol
      && first->port_source == second->port_source
      && first->port_destination == second->port_destination;
}

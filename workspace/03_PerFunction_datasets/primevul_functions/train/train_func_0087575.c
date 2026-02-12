u_int16_t ndpi_network_ptree_match(struct ndpi_detection_module_struct *ndpi_str,
                                   struct in_addr *pin ) {
  prefix_t prefix;
  patricia_node_t *node;


  fill_prefix_v4(&prefix, pin, 32, ((patricia_tree_t *) ndpi_str->protocols_ptree)->maxbits);
  node = ndpi_patricia_search_best(ndpi_str->protocols_ptree, &prefix);

  return(node ? node->value.uv.user_value : NDPI_PROTOCOL_UNKNOWN);
}

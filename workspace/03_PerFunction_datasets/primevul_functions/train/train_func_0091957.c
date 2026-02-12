Status HoistChainForConcat(const int prefix_length, const ChainLinkSet& tails,
                             NodeDef* concat_node) {
    const string& concat_name = concat_node->name();
    const int first_input = concat_node->op() == "Concat" ? 1 : 0;
    for (const auto& link : tails) {
      NodeDef* tail = CHECK_NOTNULL(link.node);
      const int concat_port = link.port_origin;
      CHECK_GE(concat_port, 0);
      CHECK_LT(concat_port, concat_node->input_size());
      const string concat_input = concat_node->input(concat_port);

      const string tail_input = tail->input(0);
      concat_node->set_input(concat_port, tail_input);
      ctx().node_map->UpdateInput(concat_name, concat_input, tail_input);

      if (concat_port == first_input) {


        UpdateConsumers(concat_node, concat_input);

        tail->set_input(0, concat_name);
        ctx().node_map->UpdateInput(tail->name(), tail_input, concat_name);
      }
    }
    return Status::OK();
  }

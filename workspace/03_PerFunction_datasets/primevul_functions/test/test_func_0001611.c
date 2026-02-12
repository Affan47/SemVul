void DependencyOptimizer::GroupCrossDeviceControlEdges(bool host_granularity) {
  VLOG(1)
      << "DependencyOptimizer::GroupCrossDeviceControlEdges host_granularity="
      << host_granularity;
  const int num_nodes = optimized_graph_->node_size();
  for (int i = 0; i < num_nodes; ++i) {
    NodeDef* node = optimized_graph_->mutable_node(i);
    if (node->device().empty()) continue;
    string rest, node_device = node->device();
    if (host_granularity) {
      DeviceNameUtils::SplitDeviceName(node->device(), &node_device, &rest);
    }


    std::map<string, NodeDef*> noops;
    int num_noops = 0;
    for (int j = 0; j < node->input_size(); ++j) {
      if (IsControlInput(node->input(j))) {
        const NodeDef* input = node_map_->GetNode(node->input(j));
        if (input == nullptr || input->device().empty()) continue;
        string input_device = input->device();
        if (host_granularity) {
          DeviceNameUtils::SplitDeviceName(input->device(), &input_device,
                                           &rest);
        }
        if (input_device != node_device) {
          VLOG(2) << "Cross-device " << node->name() << " " << input->device()
                  << " -> " << node->device();
          auto emplace_result = noops.emplace(input_device, nullptr);
          if (!emplace_result.second &&
              emplace_result.first->second == nullptr) {
            VLOG(2) << "Duplicate input device from " << node->name();


            string group_name;
            NodeDef* noop;


            do {
              group_name = AddPrefixToNodeName(
                  node->name(),
                  strings::StrCat("GroupCrossDeviceControlEdges_", num_noops));
              noop = node_map_->GetNode(group_name);
              ++num_noops;
            } while (noop != nullptr);
            noop = optimized_graph_->add_node();
            noop->set_name(group_name);
            noop->set_device(input->device());
            noop->set_op("NoOp");
            node_map_->AddNode(noop->name(), noop);
            emplace_result.first->second = noop;
            VLOG(1) << "GroupCrossDeviceControlEdges: Added "
                    << SummarizeNodeDef(*noop);
          }
        }
      }
    }


    int pos = 0;
    while (pos < node->input_size()) {
      const string& input_name = node->input(pos);
      if (IsControlInput(input_name)) {
        NodeDef* input = node_map_->GetNode(input_name);
        if (input == nullptr) {
          ++pos;
        } else {
          string input_device = input->device();
          if (host_granularity) {
            DeviceNameUtils::SplitDeviceName(input->device(), &input_device,
                                             &rest);
          }
          auto it = noops.find(input_device);
          if (it == noops.end() || it->second == nullptr) {
            ++pos;
          } else {
            VLOG(2) << "Rewriting input from " << input_name;
            node->mutable_input()->SwapElements(pos, node->input_size() - 1);
            node->mutable_input()->RemoveLast();
            it->second->add_input(AsControlDependency(*input));
            node_map_->UpdateOutput(input_name, node->name(),
                                    it->second->name());
          }
        }
      } else {
        ++pos;
      }
    }
    for (const auto& entry : noops) {
      if (entry.second) {
        node->add_input(AsControlDependency(*entry.second));
        node_map_->AddOutput(entry.second->name(), node->name());
      }
    }
  }
}

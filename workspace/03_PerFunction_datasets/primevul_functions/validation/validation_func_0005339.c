Status GraphConstructor::PopulateMissingUnusedInputMapKeys() {
  if (missing_unused_input_map_keys_ == nullptr) return Status::OK();
  for (const auto& input_map_pair : opts_.input_map) {
    TensorId key = input_map_pair.first;
    if (used_input_map_keys_.count(key) > 0) continue;

    auto pair = gdef_nodes_.find(key.first);
    if (pair == gdef_nodes_.end()) {

      missing_unused_input_map_keys_->push_back(key);
      continue;
    }


    const NodeDef& node_def = get_node_def(pair->second.gdef_index);
    const OpDef* op_def;
    TF_RETURN_IF_ERROR(g_->op_registry()->LookUpOpDef(node_def.op(), &op_def));
    int num_outputs;
    TF_RETURN_IF_ERROR(NumOutputsForNode(node_def, *op_def, &num_outputs));
    if (key.second >= num_outputs) {

      missing_unused_input_map_keys_->push_back(key);
    }
  }
  return Status::OK();
}

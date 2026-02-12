void GraphConstructor::UniquifyNames(
    const std::vector<bool>& input_already_exists, NodeDef* node_def) {
  if (NameExistsInGraph(node_def->name())) {
    string old_name = node_def->name();
    node_def->set_name(FindUniqueName(node_def->name()));
    uniquified_names_[old_name] = node_def->name();


  }
  for (int i = 0; i < node_def->input_size(); ++i) {


    if (input_already_exists[i]) continue;
    TensorId id = ParseTensorName(node_def->input(i));


    auto iter = uniquified_names_.find(string(id.first));
    if (iter == uniquified_names_.end()) continue;
    id.first = iter->second;
    node_def->set_input(i, id.ToString());
  }
}

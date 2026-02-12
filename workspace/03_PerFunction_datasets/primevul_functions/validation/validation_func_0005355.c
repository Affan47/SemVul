void GraphConstructor::AddControlDependencies(
    NodeDef* node_def, std::vector<bool>* input_already_exists) {


  bool inherits_deps = false;
  for (int i = 0; i < node_def->input_size(); ++i) {


    if ((*input_already_exists)[i]) continue;


    TensorId id(ParseTensorName(node_def->input(i)));
    auto iter = gdef_nodes_.find(id.first);
    DCHECK(iter != gdef_nodes_.end()) << id.first;
    if (iter->second.node == nullptr) {

      continue;
    }
    inherits_deps = true;
  }
  if (inherits_deps) return;


  for (const string& control_dep : opts_.control_dependencies) {
    string input = TensorId(control_dep, Graph::kControlSlot).ToString();
    bool found = false;
    for (int i = node_def->input_size() - 1; i >= 0; --i) {
      const string& node_input = node_def->input(i);
      if (node_input[0] != '^') {


        break;
      }
      if (node_input == input) {

        found = true;
        break;
      }
    }
    if (found) {
      continue;
    }
    node_def->add_input(input);
    input_already_exists->push_back(true);
  }
}

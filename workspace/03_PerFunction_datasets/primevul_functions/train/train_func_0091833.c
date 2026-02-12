InputAndShape UpdateInputs(const string& input_0, const string& input_1,
                             NodeDef* node) {
    string old_input_0 = node->input(0);
    string old_input_1 = node->input(1);


    if (old_input_0 != input_0 || old_input_1 != input_1) {
      node->set_input(0, input_0);
      node->set_input(1, input_1);

      ctx().graph_properties->ClearOutputProperties(node->name());
      ctx().graph_properties->ClearInputProperties(node->name());

      ctx().node_map->RemoveOutput(NodeName(old_input_0), node->name());
      ctx().node_map->RemoveOutput(NodeName(old_input_1), node->name());
      ctx().node_map->AddOutput(NodeName(input_0), node->name());
      ctx().node_map->AddOutput(NodeName(input_1), node->name());

      AddToOptimizationQueue(node);
    }

    TensorShapeProto shape;
    return InputAndShape(node->name(), shape);
  }

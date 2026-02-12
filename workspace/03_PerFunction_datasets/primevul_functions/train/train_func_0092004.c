Status TrySimplify(NodeDef* node, string* simplified_node_name) override {
    NodeDef* input;
    TF_RETURN_IF_ERROR(GetInputNode(node->input(0), &input));


    if (IsValueAndOrderPreserving(*node) && IsReshape(*input) &&
        !IsInPreserveSet(*input)) {
      ForwardControlDependencies(node, {input});
      node->set_input(0, input->input(0));
      ctx().node_map->UpdateInput(node->name(), input->name(), input->input(0));
      *simplified_node_name = node->name();
      AddToOptimizationQueue(node);
      return Status::OK();
    }


    if (InputMatchesTargetShape(*node) && !HasControlInputs(*node)) {
      *simplified_node_name = node->input(0);
      return Status::OK();
    }

    return Status::OK();
  }

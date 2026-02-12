Status TrySimplify(NodeDef* reduction_node,
                     string* simplified_node_name) override {
    if (IsInPreserveSet(*reduction_node)) {
      return Status::OK();
    }

    NodeDef* inner_function;
    TF_RETURN_IF_ERROR(GetInputNode(reduction_node->input(0), &inner_function));

    NodeDef* inner_function_input = nullptr;
    if (inner_function->input_size() > 0) {
      TF_RETURN_IF_ERROR(
          GetInputNode(inner_function->input(0), &inner_function_input));
    }


    auto can_be_fused_by_remapper = [](const NodeDef& consumer,
                                       const NodeDef& producer) -> bool {
      if (IsRelu(consumer) || IsRelu6(consumer)) {
        if (IsFusedBatchNorm(producer) || IsBiasAdd(producer)) {
          return true;
        }
      }
      return false;
    };
    bool is_non_decreasing = false;
    if (!IsInPreserveSet(*inner_function) &&
        IsElementWiseMonotonic(*inner_function, &is_non_decreasing) &&
        ctx().node_map->GetOutputs(inner_function->name()).size() == 1 &&
        (is_non_decreasing || !IsAnyMaxPool(*reduction_node)) &&
        !can_be_fused_by_remapper(*inner_function, *inner_function_input)) {

      NodeDef* inner_input;
      TF_RETURN_IF_ERROR(GetInputNode(inner_function->input(0), &inner_input));
      reduction_node->set_input(0, inner_input->name());
      ctx().node_map->UpdateInput(reduction_node->name(),
                                  inner_function->name(), inner_input->name());
      inner_function->set_input(0, reduction_node->name());
      UpdateConsumers(reduction_node, inner_function->name());
      ctx().node_map->UpdateInput(inner_function->name(), inner_input->name(),
                                  reduction_node->name());
      if (!is_non_decreasing) {


        const string opposite = FlipMinMax(*reduction_node);
        reduction_node->set_op(opposite);
      }

      if (IsArgMax(*reduction_node) || IsArgMin(*reduction_node)) {

        inner_function->set_op("Identity");
      }

      AddToOptimizationQueue(reduction_node);
      AddToOptimizationQueue(inner_function);
      AddToOptimizationQueue(inner_input);
    }
    return Status::OK();
  }

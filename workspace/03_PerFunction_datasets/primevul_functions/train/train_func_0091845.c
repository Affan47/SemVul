Status TrySimplify(NodeDef* node, string* simplified_node_name) override {
    NodeDef* b;
    TF_RETURN_IF_ERROR(GetInputNode(node->input(0), &b));


    if (IsSub(*b) && !IsInPreserveSet(*b) &&
        (NumNonControlOutputs(*b, *ctx().node_map) == 1)) {


      const DataType type = GetDataTypeFromAttr(*b, "T");
      if ((type == DT_COMPLEX64) || (type == DT_COMPLEX128))
        return Status::OK();
      node->set_op("Identity");
      b->set_op("SquaredDifference");
      AddToOptimizationQueue(node);
      AddToOptimizationQueue(b);
    }
    return Status::OK();
  }

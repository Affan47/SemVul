Status TrySimplifyInternal(NodeDef* node, NodeDef* add_node, int i, int j,
                             bool* modified) {
    const auto& t =
        ctx().graph_properties->GetInputProperties(add_node->name())[i];
    const auto& c =
        ctx().graph_properties->GetInputProperties(add_node->name())[j];
    for (int k = 0; k < c.shape().dim_size(); ++k) {

      if (c.shape().dim(k).size() < 0) {
        return Status::OK();
      }
    }
    TensorShapeProto broadcast_shape;
    if (!ShapeAfterBroadcast(t.shape(), c.shape(), &broadcast_shape)) {
      return Status::OK();
    }
    if (!ShapesSymbolicallyEqual(t.shape(), broadcast_shape)) {


      return Status::OK();
    }
    Tensor constant;
    if (GetTensorFromConstNode(add_node->input(j), &constant)) {
      complex128 element;


      for (int k = 0; k < constant.NumElements(); ++k) {
        if (!GetElementUnexhaustive(constant, k,
                                    {DT_BFLOAT16, DT_HALF, DT_FLOAT, DT_DOUBLE,
                                     DT_COMPLEX64, DT_COMPLEX128},
                                    &element)) {

          return Status::OK();
        }
        if (element != complex128(1)) {

          return Status::OK();
        }
      }
      NodeDef *x, *y;
      TF_RETURN_IF_ERROR(GetInputNode(add_node->input(i), &x));
      TF_RETURN_IF_ERROR(GetInputNode(add_node->input(j), &y));
      node->set_op("Log1p");
      node->set_input(0, add_node->input(i));
      node->add_input(AsControlDependency(y->name()));
      ForwardControlDependencies(node, {add_node});

      AddToOptimizationQueue(node);
      AddToOptimizationQueue(add_node);
      AddToOptimizationQueue(x);
      AddToOptimizationQueue(y);
      *modified = true;
    }
    return Status::OK();
  }

Status TrySimplify(NodeDef* node, string* simplified_node_name) override {
#define TF_RETURN_IF_TRUE(...) \
  if ((__VA_ARGS__)) return Status::OK()

    NodeDef* conv = node;

    NodeDef* weights;
    TF_RETURN_IF_ERROR(GetInputNode(conv->input(1), &weights));


    TF_RETURN_IF_TRUE(!IsConstant(*weights));


    const string scaled_weights_node_name =
        OptimizedNodeName(ParseNodeScopeAndName(weights->name()),
                          strings::StrCat("scaled", "_", conv->name()));

    TF_RETURN_IF_TRUE(ctx().node_map->NodeExists(scaled_weights_node_name));


    NodeDef* tail = GetTailOfValuePreservingChain(*conv, *ctx().node_map,
                                                  *ctx().nodes_to_preserve);

    NodeDef* source;
    TF_RETURN_IF_ERROR(GetInputNode(tail->input(0), &source));


    TF_RETURN_IF_TRUE(!IsAnyMul(*source));
    TF_RETURN_IF_TRUE(NumNonControlOutputs(*source, *ctx().node_map) != 1);

    TF_RETURN_IF_TRUE(IsInPreserveSet(*source));

    const NodeDef* mul = source;
    int input_idx = 0;
    int scale_idx = 1;
    NodeDef* scale;
    NodeDef* input;
    TF_RETURN_IF_ERROR(GetInputNode(mul->input(scale_idx), &scale));
    TF_RETURN_IF_ERROR(GetInputNode(mul->input(input_idx), &input));
    if (!IsConstant(*scale) && IsConstant(*input)) {
      VLOG(3) << "Swapped inputs to mul";
      std::swap(scale_idx, input_idx);
      std::swap(scale, input);
    }
    TF_RETURN_IF_TRUE(!IsConstant(*scale));


    const TensorProto& scale_tensor = scale->attr().at("value").tensor();
    bool scale_is_a_scalar = scale_tensor.has_tensor_shape() &&
                             scale_tensor.tensor_shape().dim_size() == 0;
    TF_RETURN_IF_TRUE(!scale_is_a_scalar);


    TF_RETURN_IF_TRUE(!IsConstant(*scale));
    TF_RETURN_IF_ERROR(CheckAttrsExist(*scale, {"dtype"}));
    TF_RETURN_IF_ERROR(CheckAttrExists(*weights, "dtype"));
    TF_RETURN_IF_TRUE(scale->attr().at("dtype").type() !=
                      weights->attr().at("dtype").type());


    VLOG(3) << "Fold multiply into conv: conv=" << conv->name()
            << " mul=" << mul->name() << " weights=" << weights->name();


    NodeDef* scaled_weights = AddEmptyNode(scaled_weights_node_name);
    scaled_weights->set_op(source->op());
    scaled_weights->set_device(weights->device());
    (*scaled_weights->mutable_attr())["T"] = weights->attr().at("dtype");
    AddToOptimizationQueue(scaled_weights);


    scaled_weights->add_input(conv->input(1));
    ctx().node_map->AddOutput(weights->name(), scaled_weights->name());
    scaled_weights->add_input(mul->input(scale_idx));
    ctx().node_map->AddOutput(scale->name(), scaled_weights->name());
    ForwardControlDependencies(scaled_weights, {source});


    conv->set_input(1, scaled_weights->name());
    ctx().node_map->UpdateInput(conv->name(), weights->name(),
                                scaled_weights->name());
    AddToOptimizationQueue(conv);


    tail->set_input(0, mul->input(input_idx));
    ctx().node_map->UpdateInput(tail->name(), mul->name(), input->name());
    AddToOptimizationQueue(tail);
    *simplified_node_name = conv->name();

    return Status::OK();
#undef TF_RETURN_IF_TRUE
  }

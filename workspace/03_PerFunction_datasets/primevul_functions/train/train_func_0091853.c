string RewriteOptimizedNodesGroup(const OptimizedNodesGroup& group) override {
    VLOG(2) << "Collapse Add/AddN: root=" << group.root_node->name()
            << " op=" << group.root_node->op()
            << " num_optimized_nodes=" << group.optimized_nodes.size()
            << " num_inputs=" << group.inputs.size();


    MarkAllMembersWithTag(group, kAddOpsRewriteTag);


    auto root_scope_and_name = ParseNodeScopeAndName(group.root_node->name());


    std::unordered_map<string, std::vector<InputAndShape>> shape_sig_to_inputs;
    for (const auto& input : group.inputs) {
      shape_sig_to_inputs[ShapeSignature(input.shape)].push_back(input);
    }

    using SigKV = decltype(shape_sig_to_inputs)::value_type;
    VLOG(3) << "Add/AddN group has " << shape_sig_to_inputs.size()
            << " unique shapes: "
            << absl::StrJoin(shape_sig_to_inputs, ", ",
                             [](string* out, SigKV p) {
                               strings::StrAppend(out, p.first);
                             });


    std::vector<TensorShapeProto> shapes;
    shapes.reserve(shape_sig_to_inputs.size());
    for (const auto& el : shape_sig_to_inputs)
      shapes.push_back(el.second[0].shape);


    if (shapes.size() == 1) {
      string node_name = UniqueOptimizedNodeName(root_scope_and_name);
      AddInputsOfSymbolicallyEqualShape(*group.root_node, node_name,
                                        group.inputs);
      return node_name;
    }


    std::sort(shapes.begin(), shapes.end(),
              [](const TensorShapeProto& left, const TensorShapeProto& right) {
                return CompareSymbolicallyShapedTensorSizes(left, right);
              });


    auto leaf_node_name = [&root_scope_and_name, this](int i) {
      return UniqueOptimizedNodeName(root_scope_and_name,
                                     strings::StrCat("Leaf_", i));
    };

    auto internal_node_name = [&root_scope_and_name, this](int i) {
      return UniqueOptimizedNodeName(root_scope_and_name,
                                     strings::StrCat("Internal_", i));
    };


    std::deque<InputAndShape> add_ops;


    for (int i = 0, end = shapes.size(); i < end; ++i) {
      const auto node_name = leaf_node_name(i);
      const auto& inputs = shape_sig_to_inputs[ShapeSignature(shapes[i])];
      add_ops.push_back(AddInputsOfSymbolicallyEqualShape(*group.root_node,
                                                          node_name, inputs));
    }


    int internal_nodes = 0;
    do {
      const InputAndShape lhs = add_ops.front();
      add_ops.pop_front();
      const InputAndShape rhs = add_ops.front();
      add_ops.pop_front();
      string name = add_ops.empty()
                        ? UniqueOptimizedNodeName(root_scope_and_name)
                        : internal_node_name(internal_nodes++);
      InputAndShape add = AddAggregatedInputs(*group.root_node, name, lhs, rhs);
      add_ops.push_front(add);
    } while (add_ops.size() > 1);

    InputAndShape optimized_root_node = add_ops.front();
    return optimized_root_node.input;
  }

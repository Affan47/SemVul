Status ConstantFold(const ConstantFoldingOptions& opts,
                    FunctionLibraryRuntime* function_library, Env* env,
                    const Device* partition_device, Graph* graph,
                    bool* was_mutated) {


  port::ScopedFlushDenormal flush;
  port::ScopedSetRound round(FE_TONEAREST);

  DumpGraph("Before", graph);
  ConstantFoldNameGenerator generate_new_name = opts.generate_new_name;
  if (generate_new_name == nullptr) {
    generate_new_name = [](Graph* graph, string old_name) {
      return strings::StrCat(graph->NewName(old_name), "__cf__",
                             UniqueConstantId());
    };
  }

  std::vector<Node*> constant_foldable_nodes;
  std::unordered_map<const Node*, gtl::FlatSet<Node*>> constant_control_deps;
  std::unordered_map<const Node*, std::vector<Tensor>> shape_replacement_map;
  FindConstantFoldableNodes(graph, opts, &constant_foldable_nodes,
                            &constant_control_deps, &shape_replacement_map);
  if (constant_foldable_nodes.empty()) {
    VLOG(1) << "No constant foldable nodes found";
    *was_mutated = false;

    return Status::OK();
  }

  std::map<NodeAndOutput, NodeAndOutput> tensors_to_fetch;
  std::unique_ptr<Graph> constant_graph(
      GetConstantGraph(graph, constant_foldable_nodes, shape_replacement_map,
                       &tensors_to_fetch, generate_new_name));
  DumpGraph("Constant graph", constant_graph.get());

  if (tensors_to_fetch.empty()) {
    VLOG(1) << "No constant nodes found that feed into the original graph.";
    *was_mutated = false;

    return Status::OK();
  }
  VLOG(1) << "Constant foldable " << constant_graph->num_node_ids() << " : "
          << graph->num_node_ids();

  std::vector<string> tensors_to_fetch_names;
  std::vector<NodeAndOutput> tensors_to_replace;


  std::vector<std::pair<NodeAndOutput, NodeAndOutput>> tensors_to_fetch_sorted(
      tensors_to_fetch.begin(), tensors_to_fetch.end());
  std::sort(tensors_to_fetch_sorted.begin(), tensors_to_fetch_sorted.end(),
            [](const std::pair<NodeAndOutput, NodeAndOutput>& n1,
               const std::pair<NodeAndOutput, NodeAndOutput>& n2) {
              return std::tie(n1.first.first->name(), n1.first.second) <
                     std::tie(n2.first.first->name(), n2.first.second);
            });
  for (auto n : tensors_to_fetch_sorted) {
    tensors_to_fetch_names.push_back(
        strings::StrCat(n.first.first->name(), ":", n.first.second));
    tensors_to_replace.push_back(n.second);
  }

  auto graph_runner = std::unique_ptr<GraphRunner>(new GraphRunner(env));

  std::vector<Tensor> outputs;
  auto delete_tensors = gtl::MakeCleanup([&graph_runner, &outputs] {

    outputs.clear();
    graph_runner.reset(nullptr);
  });

  Status s =
      graph_runner->Run(constant_graph.get(), function_library, {} ,
                        tensors_to_fetch_names, &outputs);
  if (!s.ok()) {
    VLOG(1) << "Could not fetch constants: " << s;
    *was_mutated = false;
    return s;
  }


  int32_t num_nodes_replaced = 0;
  for (size_t c = 0; c < outputs.size(); ++c) {
    const gtl::FlatSet<Node*>& control_deps =
        constant_control_deps[tensors_to_replace[c].first];
    if (ReplaceTensorWithConstant(
            graph, partition_device, tensors_to_replace[c], outputs[c],
            control_deps, opts.max_constant_size_in_bytes, generate_new_name)) {
      ++num_nodes_replaced;
    }
  }

  DumpGraph("After", graph);

  *was_mutated = (num_nodes_replaced > 0);
  return Status::OK();
}

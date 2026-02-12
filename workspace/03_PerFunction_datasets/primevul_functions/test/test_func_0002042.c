Status GraphProperties::InferStatically(bool assume_valid_feeds,
                                        bool aggressive_shape_inference,
                                        bool include_input_tensor_values,
                                        bool include_output_tensor_values) {
  FunctionLibraryDefinition function_library(OpRegistry::Global(),
                                             item_.graph.library());
  absl::flat_hash_map<string, absl::flat_hash_set<int>> fed_ports;
  if (!assume_valid_feeds) {
    for (const auto& feed : item_.feed) {
      SafeTensorId tensor_id = ParseTensorName(feed.first);
      fed_ports[tensor_id.node()].insert(tensor_id.index());
    }
  }

  GraphView graph_view(&item_.graph);


  absl::flat_hash_map<const NodeDef*,
                      std::pair<absl::flat_hash_set<const NodeDef*>,
                                absl::flat_hash_set<const NodeDef*>>>
      resources;
  absl::flat_hash_set<const NodeDef*> merge_nodes;
  absl::flat_hash_set<const NodeDef*> fed_nodes;
  absl::flat_hash_set<const NodeDef*> primary_inputs;
  int num_loops = 0;
  for (const NodeDef& node : item_.graph.node()) {
    if (IsQueue(node)) {
      for (const GraphView::InputPort& fanout :
           graph_view.GetFanouts(node, false)) {
        if (IsEnter(*fanout.node)) {
          const NodeDef& enter = *fanout.node;
          for (const GraphView::InputPort& fanout :
               graph_view.GetFanouts(enter, false)) {
            if (IsEnqueue(*fanout.node)) {
              resources[&node].first.insert(fanout.node);
            } else if (IsDequeue(*fanout.node)) {
              resources[&node].second.insert(fanout.node);
            }
          }
        } else {
          if (IsEnqueue(*fanout.node)) {
            resources[&node].first.insert(fanout.node);
          } else if (IsDequeue(*fanout.node)) {
            resources[&node].second.insert(fanout.node);
          }
        }
      }
    }
    if (!HasRegularInputs(node)) {
      primary_inputs.insert(&node);
    } else if (IsMerge(node)) {
      merge_nodes.insert(&node);
    } else if (IsNextIteration(node)) {
      ++num_loops;
    }
    if (fed_ports.find(node.name()) != fed_ports.end()) {
      fed_nodes.insert(&node);
    }
  }

  absl::flat_hash_map<const NodeDef*, const NodeDef*> resource_handles;
  std::vector<TopologicalDependency> extra_deps;
  for (const auto& resource : resources) {
    for (const NodeDef* src : resource.second.first) {
      resource_handles[src] = resource.first;
      for (const NodeDef* dst : resource.second.second) {


        extra_deps.emplace_back(src, dst);
      }
    }
  }

  std::vector<const NodeDef*> topo_order;
  Status s = ComputeTopologicalOrder(item_.graph, extra_deps, &topo_order);
  if (!s.ok()) {
    if (extra_deps.empty()) {
      return s;
    } else {


      TF_RETURN_IF_ERROR(ComputeTopologicalOrder(item_.graph, &topo_order));
    }
  }


  auto refiner = absl::make_unique<SymbolicShapeRefiner>(
      graph_view, fed_ports, aggressive_shape_inference);

  TopoQueue new_shapes(topo_order);

  for (const NodeDef* node : primary_inputs) {
    new_shapes.push(node);
  }

  for (const NodeDef* node : fed_nodes) {
    new_shapes.push(node);
  }

  TF_RETURN_IF_ERROR(
      PropagateShapes(refiner.get(), &new_shapes, resource_handles, num_loops));


  std::unique_ptr<SymbolicShapeManager> shape_manager =
      absl::make_unique<SymbolicShapeManager>();
  bool found_error = false;
  for (const NodeDef& node : item_.graph.node()) {
    auto node_ctx = refiner->GetContext(&node);
    if (!node_ctx) {
      continue;
    }

    if (fed_ports.find(node.name()) != fed_ports.end()) {
      VLOG(2) << "Skipping feed node shape: " << node.name();
      continue;
    }
    for (const auto& merged_shapes : node_ctx->MergedShapes()) {
      if (!shape_manager->Merge(merged_shapes.first, merged_shapes.second)
               .ok()) {
        found_error = true;
        break;
      }
    }
    for (const auto& merged_dims : node_ctx->MergedDims()) {
      if (!shape_manager->Merge(merged_dims.first, merged_dims.second).ok()) {
        found_error = true;
        break;
      }
    }
    if (found_error) {


      shape_manager = absl::make_unique<SymbolicShapeManager>();
      break;
    }
  }

  TF_RETURN_IF_ERROR(ValidateSymbolicShapeManager(item_.graph, refiner.get(),
                                                  shape_manager.get()));

  for (const NodeDef& node : item_.graph.node()) {
    VLOG(4) << "Filling in graph properties for node: " << node.name();
    auto ctx = refiner->GetNodeContext(&node);
    if (!ctx) {
      continue;
    }

    auto* ic = ctx->inference_context.get();


    {
      auto& input_properties = input_properties_[node.name()];


      CHECK_EQ(input_properties.size(), 0);

      input_properties.resize(ic->num_inputs());
      GraphView::InputPort input(&node, -1);
      for (int i = 0; i < ic->num_inputs(); ++i) {
        shape_manager->AsTensorProperties(ic->input(i), ctx->input_types[i],
                                          &input_properties[i]);
        input.port_id = i;
        GraphView::OutputPort fanin = graph_view.GetRegularFanin(input);
        if (include_input_tensor_values) {

          if (IsConstant(*fanin.node)) {
            const TensorProto& raw_val =
                fanin.node->attr().at("value").tensor();
            *input_properties[i].mutable_value() = raw_val;
          } else if (static_cast<int>(ctx->input_tensor_protos.size()) > i &&
                     ctx->input_tensor_protos[i] != nullptr) {
            *input_properties[i].mutable_value() = *ctx->input_tensor_protos[i];
          } else if (static_cast<int>(ic->input_tensors_as_shapes().size()) >
                         i &&
                     IsShapeFullyDefinedIntegerVectorOrScalar(
                         ic, ic->input(i), ic->input_tensors_as_shapes()[i],
                         ctx->input_types[i])) {
            *input_properties[i].mutable_value() = MakeTensorProtoFromShape(
                ic, ic->input(i), ic->input_tensors_as_shapes()[i],
                ctx->input_types[i]);
          }
        }
      }
    }


    {
      auto& output_properties = output_properties_[node.name()];


      CHECK_EQ(output_properties.size(), 0);

      output_properties.resize(ic->num_outputs());
      for (int i = 0; i < ic->num_outputs(); ++i) {
        shape_manager->AsTensorProperties(ic->output(i), ctx->output_types[i],
                                          &output_properties[i]);
        auto converted_output_tensors_as_shapes =
            ReplaceUnknownDimFromConstWithUnknownDim(
                ic, ctx->output_tensors_as_shapes);
        if (include_output_tensor_values) {

          if (IsConstant(node)) {

            const TensorProto& raw_val = node.attr().at("value").tensor();
            *output_properties[i].mutable_value() = raw_val;
          } else if (static_cast<int>(ctx->output_tensor_protos.size()) > i &&
                     ctx->output_tensor_protos[i] != nullptr) {
            *output_properties[i].mutable_value() =
                *ctx->output_tensor_protos[i];
          } else if (static_cast<int>(
                         converted_output_tensors_as_shapes.size()) > i &&
                     IsShapeFullyDefinedIntegerVectorOrScalar(
                         ic, ic->output(i),
                         converted_output_tensors_as_shapes[i],
                         ctx->output_types[i])) {
            *output_properties[i].mutable_value() = MakeTensorProtoFromShape(
                ic, ic->output(i), converted_output_tensors_as_shapes[i],
                ctx->output_types[i]);
          }
        }
      }
    }

    if (aggressive_shape_inference && ctx->shape_incompatible)
      incompatible_shape_nodes_.insert(node.name());
  }

  if (aggressive_shape_inference && !incompatible_shape_nodes_.empty())
    LOG(WARNING) << incompatible_shape_nodes_.size()
                 << " nodes have incompatible output shapes.";


  VerboseLogUnknownDimensionSources(item_.graph, input_properties_,
                                    output_properties_);

  TF_RETURN_IF_ERROR(VerboseShapeInferenceLogging(item_.graph, refiner.get(),
                                                  shape_manager.get()));

  return Status::OK();
}

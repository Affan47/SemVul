Status UpdateNode(const NodeDef* node, bool* refined) {
    NodeContext* ctx = GetNodeContext(node);
    if (ctx == nullptr) {
      TF_RETURN_IF_ERROR(AddNode(node));
      ctx = CHECK_NOTNULL(GetNodeContext(node));
      *refined = true;
    }


    InferenceContext* ic = ctx->inference_context.get();
    ctx->input_tensors_as_shapes_to_propagate.resize(ic->num_inputs());
    ctx->input_tensor_protos.resize(ic->num_inputs(), nullptr);

    for (int dst_input = 0; dst_input < ic->num_inputs(); ++dst_input) {
      const GraphView::InputPort port(node, dst_input);
      const GraphView::OutputPort fanin = graph_.GetRegularFanin(port);
      int src_output = fanin.port_id;
      const NodeDef* src = fanin.node;
      NodeContext* src_ctx = GetNodeContext(src);
      if (src_ctx == nullptr) {
        return errors::FailedPrecondition(
            "Input ", dst_input, " for '", node->name(),
            "' was not previously added to SymbolicShapeRefiner.");
      }

      InferenceContext* src_ic = src_ctx->inference_context.get();
      if (src_output >= src_ic->num_outputs()) {
        return errors::OutOfRange("src_output = ", src_output,
                                  ", but num_outputs is only ",
                                  src_ic->num_outputs());
      }


      if (static_cast<int>(src_ctx->output_tensors_as_shapes.size()) >
          src_output) {
        ctx->input_tensors_as_shapes_to_propagate[dst_input] =
            src_ctx->output_tensors_as_shapes[src_output];
      }

      if (static_cast<int>(src_ctx->output_tensor_protos.size()) > src_output) {
        const auto* tensor_proto = src_ctx->output_tensor_protos[src_output];
        if (tensor_proto != nullptr) {
          ctx->input_tensor_protos[dst_input] = tensor_proto;
        }
      }


      if (!*refined &&
          !ic->input(dst_input).SameHandle(src_ic->output(src_output))) {
        *refined = true;
      }
      ic->SetInput(dst_input, src_ic->output(src_output));

      if (!*refined && ic->requested_input_tensor_as_partial_shape(dst_input)) {


        *refined = true;
      }


      if (ctx->input_types[dst_input] == DT_RESOURCE) {
        auto* outputs = src_ic->output_handle_shapes_and_types(src_output);
        if (!outputs) continue;
        auto* inputs = ic->input_handle_shapes_and_types(dst_input);

        if (!inputs || !EquivalentShapesAndTypes(*outputs, *inputs))
          *refined = true;
        ic->set_input_handle_shapes_and_types(dst_input, *outputs);
      }
    }


    *refined |= ic->num_inputs() == 0;

    if (!*refined) {

      return Status::OK();
    }


    ic->set_input_tensors_as_shapes(ReplaceUnknownDimFromConstWithUnknownDim(
        ic, ctx->input_tensors_as_shapes_to_propagate));


    if (ctx->op_data && ctx->op_data->is_function_op) {


      if (aggressive_shape_inference_) {


        auto s = UpdateOutputShapesUsingAnnotatedInformation(*node, ctx);
        if (s.ok() && AllOutputShapesKnown(ctx)) {
          return Status::OK();
        }


      }
      auto s = UpdateFunction(node);
      if (s.ok()) {
        return Status::OK();
      } else {
        VLOG(1) << "UpdateFunction failed for " << node->op()
                << ". Defaulting to ShapeUnknown.\n"
                << s.ToString();
      }
    }


    std::vector<Tensor> const_values(ic->num_inputs());
    std::vector<const Tensor*> input_tensors(ic->num_inputs(), nullptr);
    for (int dst_input = 0; dst_input < ic->num_inputs(); ++dst_input) {
      const TensorProto* tensor_proto = ctx->input_tensor_protos[dst_input];
      if (tensor_proto != nullptr &&

          NumElementsFromTensorProto(*tensor_proto) <=
              kThresholdToSkipConstTensorInstantiation &&
          const_values[dst_input].FromProto(*tensor_proto)) {
        input_tensors[dst_input] = &const_values[dst_input];
      }
    }
    ic->set_input_tensors(input_tensors);


    return InferShapes(*node, ctx);
  }

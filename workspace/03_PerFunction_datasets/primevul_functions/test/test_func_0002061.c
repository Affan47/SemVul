Status InferShapes(const NodeDef& node, NodeContext* c) {

    if (!c->op_data || c->op_data->shape_inference_fn == nullptr ||
        !c->inference_context->Run(c->op_data->shape_inference_fn).ok()) {


      TF_RETURN_IF_ERROR(
          c->inference_context->Run(shape_inference::UnknownShape));
    }
    Status status = Status::OK();
    auto it = fed_ports_.find(node.name());
    const bool is_fed = it != fed_ports_.end();
    if (is_fed) {


      for (const int output_port : it->second) {
        status.Update(SetUnknownShape(&node, output_port));
      }
    }


    status.Update(MaybeUpdateNodeContextOutput(node, is_fed, c));

    return status;
  }

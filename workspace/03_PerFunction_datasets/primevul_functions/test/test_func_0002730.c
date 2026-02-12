NodeDef* MutableGraphView::GetControllingFaninToAdd(absl::string_view node_name,
                                                    const OutputPort& fanin,
                                                    string* error_msg) {
  if (!IsSwitch(*fanin.node)) {
    return fanin.node;
  } else {
    if (IsOutputPortControlling(fanin)) {

      TensorId tensor_id(fanin.node->name(), fanin.port_id);
      *error_msg = absl::Substitute(
          "can't add fanin '$0' as it will become a Switch control dependency",
          tensor_id.ToString());
      return nullptr;
    }


    for (const auto& fanout : GetFanout(fanin)) {
      if (IsIdentity(*fanout.node) || IsIdentityNSingleInput(*fanout.node)) {
        if (fanout.node->name() == node_name) {
          *error_msg =
              absl::Substitute("can't add found fanin '$0' to self",
                               AsControlDependency(fanout.node->name()));
          return nullptr;
        }
        return fanout.node;
      }
    }


    if (GeneratedNameForIdentityConsumingSwitch(fanin) == node_name) {
      *error_msg = absl::Substitute("can't add generated fanin '$0' to self",
                                    AsControlDependency(string(node_name)));
    }
  }
  return nullptr;
}

bool ConstantFolding::MaybeFoldable(const NodeDef& node,
                                    const GraphProperties* properties) const {

  if (IsConstant(node)) {
    return false;
  }

  if (!IsFreeOfSideEffect(node)) {
    return false;
  }


  if (nodes_to_preserve_.find(node.name()) != nodes_to_preserve_.end() &&
      nodes_allowlist_.find(node.name()) == nodes_allowlist_.end()) {
    return false;
  }


  if (ModifiesFrameInfo(node)) {
    return false;
  }


  if (IsPlaceholder(node)) {
    return false;
  }


  if (IsFakeParam(node)) {
    return false;
  }

  if (node.op() == "AccumulateNV2") {
    return false;
  }

  if (node.op() == "LoopCond") {
    return false;
  }

  if (!fold_quantization_emulation_ && IsQuantizationEmulation(node)) {
    return false;
  }

  const string& op = node.op();
  if (op.find("Save") != string::npos || op.find("Restore") != string::npos ||
      op.find("Reader") != string::npos) {
    return false;
  }
  if (op.find("Quantized") != string::npos || absl::StartsWith(op, "Sparse")) {
    return false;
  }


  if (HasTPUAttributes(node)) {
    return false;
  }

  const OpDef* op_def = nullptr;
  Status status = OpRegistry::Global()->LookUpOpDef(node.op(), &op_def);
  if (!status.ok()) {
    return false;
  }

  if (op_def->output_arg_size() == 0) {
    return false;
  }


  for (const OpDef::ArgDef& output_arg : op_def->output_arg()) {
    if (output_arg.type() == DT_VARIANT) {
      return false;
    }
  }


  const auto& outputs = node_map_->GetOutputs(node.name());
  if (outputs.empty() &&
      nodes_allowlist_.find(node.name()) == nodes_allowlist_.end()) {
    return false;
  }
  return true;
}

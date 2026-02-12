Status GraphConstructor::ValidateShape(Node* node) {
  if (!opts_.importing || !opts_.validate_shape) return Status::OK();
  TF_RETURN_IF_ERROR(refiner_->AddNode(node));

  std::vector<const TensorShapeProto*> shape_attrs;
  const char* kAttrName = "_output_shapes";
  if (!TryGetNodeAttr(node->attrs(), kAttrName, &shape_attrs)) {

    return Status::OK();
  }
  auto* ic = refiner_->GetContext(node);
  DCHECK(ic != nullptr)
      << "ShapeRefiner::AddNode() should have created the InferenceContext";
  if (shape_attrs.size() < node->num_outputs()) {
    return errors::InvalidArgument(
        "Node '", node->name(), "' has ", node->num_outputs(),
        " outputs but the ", kAttrName, " attribute specifies shapes for ",
        shape_attrs.size(), " outputs");
  }


  if (shape_attrs.size() > node->num_outputs()) {
    LOG(WARNING) << "Node '" << node->name() << "' has " << node->num_outputs()
                 << " outputs but the " << kAttrName
                 << " attribute specifies shapes for " << shape_attrs.size()
                 << " outputs. Output shapes may be inaccurate.";
  }
  for (int i = 0; i < node->num_outputs(); ++i) {
    const TensorShapeProto& p = *shape_attrs[i];
    shape_inference::ShapeHandle h;
    Status s = ic->MakeShapeFromShapeProto(p, &h);
    if (!s.ok()) {
      return errors::InvalidArgument("Node '", node->name(), " has an invalid ",
                                     kAttrName, " attribute (shape #", i,
                                     " error:'", s.error_message(), "'");
    }
    s = refiner_->SetShape(node, i, h);
    if (!s.ok()) {
      return errors::InvalidArgument(
          "Node '", node->name(), "' has an ", kAttrName,
          " attribute inconsistent with the GraphDef for output #", i, ": ",
          s.error_message());
    }
  }
  node->ClearAttr(kAttrName);
  return Status::OK();
}

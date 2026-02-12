Status GraphConstructor::MakeNode(NodeDef&& node_def, Node** node) {

  Status status;
  *node = g_->AddNode(std::move(node_def), &status);
  if (!status.ok()) return status;
  if (opts_.expect_device_spec) {
    (*node)->set_assigned_device_name((*node)->def().device());
  }
  return Status::OK();
}

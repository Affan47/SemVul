bool ConstantFolding::IsReallyConstant(const NodeDef& node) const {
  if (!IsConstant(node)) {
    return false;
  }

  return feed_nodes_.find(node.name()) == feed_nodes_.end();
}

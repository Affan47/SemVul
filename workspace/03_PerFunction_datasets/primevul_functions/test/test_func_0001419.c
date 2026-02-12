void Node::MaybeCopyOnWrite() {


  if (!props_.unique()) {
    props_ = std::make_shared<NodeProperties>(*props_);
  }
}

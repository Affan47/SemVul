Add(const XMLNode& node) {
    XMLNode *new_node = new XMLNode(node);
    nodes_.push_back(new_node);
  }

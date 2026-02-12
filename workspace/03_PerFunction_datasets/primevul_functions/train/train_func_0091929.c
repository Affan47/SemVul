bool IsReallyConstant(const NodeDef& node) const {
    if (!IsConstant(node)) {
      return false;
    }

    return ctx().feed_nodes->find(node.name()) == ctx().feed_nodes->end();
  }

bool IsRewritten(const NodeDef* node) const {


    return rewritten_nodes_.find(node->name()) != rewritten_nodes_.end() ||
           ctx().node_map->NodeExists(OuterNodeName(node, false)) ||
           ctx().node_map->NodeExists(OuterNodeName(node, true)) ||
           ctx().node_map->NodeExists(InnerAddNodeName(node));
  }

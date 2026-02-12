bool IsSupported(const NodeDef* node) const override {
    return CanOptimize(*node) &&


           !ctx().node_map->NodeExists(OptimizedNodeName(*node));
  }

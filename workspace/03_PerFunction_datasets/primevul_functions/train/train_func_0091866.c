bool IsAbsorbableByOptimizedNodesGroup(const OptimizedNodesGroup& group,
                                         const NodeDef& node) const override {
    if (!CanOptimize(node)) return false;

    if (!IsOnTheSameDevice(group, node)) {
      return false;
    }


    if (NumNonControlDataOutputs(node, *ctx().node_map) != 1) {
      return false;
    }

    const OpInfo::TensorProperties* properties;
    Status has_properties = GetTensorProperties(node.name(), &properties);
    return has_properties.ok() &&
           HasAllInputsBroadcastableToShape(node, *properties);
  }

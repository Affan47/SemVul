bool IsSupported(const NodeDef* node) const override {
    if (!IsBinaryAssociative(*node)) return false;

    if (IsMarkedWithAnyTag(*node, kMinimizeBroadcastsTag, kAddOpsRewriteTag))
      return false;


    const OpInfo::TensorProperties* properties;
    Status has_properties = GetTensorProperties(node->name(), &properties);
    return has_properties.ok() && ShapeIsSymbolicallyDefined(*properties) &&
           HasAllInputsBroadcastableToShape(*node, *properties);
  }

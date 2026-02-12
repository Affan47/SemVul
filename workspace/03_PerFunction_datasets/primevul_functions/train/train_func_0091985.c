bool IsSupported(const NodeDef* node) const override {
    if (IsInPreserveSet(*node)) return false;
    if (IsConcat(*node) && node->attr().count("N") != 0) {
      const int n = node->attr().at("N").i();
      return n > 1 && FirstNInputsAreUnique(*node, n);
    } else if ((IsSplit(*node) || IsSplitV(*node)) &&
               node->attr().count("num_split") != 0) {
      const int num_split = node->attr().at("num_split").i();
      if (NumNonControlOutputs(*node, *ctx().node_map) > num_split) {


        return false;
      }
      if (NumControlOutputs(*node, *ctx().node_map) > 0) {


        return false;
      }
      return num_split > 1 && !IsAlreadyOptimized(*node);
    }
    return false;
  }

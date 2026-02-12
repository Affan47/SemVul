bool CanOptimize(const NodeDef& node) const {

    if (!IsAdd(node) && !IsAddN(node)) {
      return false;
    }
    if (IsInPreserveSet(node) || IsMarkedWithTag(node, kAddOpsRewriteTag)) {
      return false;
    }

    return !(IsDrivenByControlDependency(node) ||
             DrivesControlDependency(node));
  }

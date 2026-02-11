IsSmallObject(const GlobalValue *GV, const XCoreTargetLowering &XTL) {
  if (XTL.getTargetMachine().getCodeModel() == CodeModel::Small)
    return true;

  Type *ObjType = GV->getType()->getPointerElementType();
  if (!ObjType->isSized())
    return false;

  auto &DL = GV->getParent()->getDataLayout();
  unsigned ObjSize = DL.getTypeAllocSize(ObjType);
  return ObjSize < CodeModelLargeSize && ObjSize != 0;
}

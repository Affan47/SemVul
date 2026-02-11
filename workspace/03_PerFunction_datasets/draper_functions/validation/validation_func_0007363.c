runOnFunction(Function &Fn) {
  F = &Fn;
  M = F->getParent();
  DominatorTreeWrapperPass *DTWP =
      getAnalysisIfAvailable<DominatorTreeWrapperPass>();
  DT = DTWP ? &DTWP->getDomTree() : nullptr;
  TLI = TM->getSubtargetImpl(Fn)->getTargetLowering();

  Attribute Attr = Fn.getFnAttribute("stack-protector-buffer-size");
  if (Attr.isStringAttribute() &&
      Attr.getValueAsString().getAsInteger(10, SSPBufferSize))
      return false;

  if (!RequiresStackProtector())
    return false;

  ++NumFunProtected;
  return InsertStackProtectors();
}

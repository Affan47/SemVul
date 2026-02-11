getModRefInfo(ImmutableCallSite CS,
                                            const MemoryLocation &Loc) {
  if (!EnableTBAA)
    return AAResultBase::getModRefInfo(CS, Loc);

  if (const MDNode *L = Loc.AATags.TBAA)
    if (const MDNode *M =
            CS.getInstruction()->getMetadata(LLVMContext::MD_tbaa))
      if (!Aliases(L, M))
        return MRI_NoModRef;

  return AAResultBase::getModRefInfo(CS, Loc);
}

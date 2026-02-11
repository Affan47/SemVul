getModRefInfo(ImmutableCallSite CS,
                                                const MemoryLocation &Loc) {
  if (!EnableScopedNoAlias)
    return AAResultBase::getModRefInfo(CS, Loc);

  if (!mayAliasInScopes(Loc.AATags.Scope, CS.getInstruction()->getMetadata(
                                              LLVMContext::MD_noalias)))
    return MRI_NoModRef;

  if (!mayAliasInScopes(
          CS.getInstruction()->getMetadata(LLVMContext::MD_alias_scope),
          Loc.AATags.NoAlias))
    return MRI_NoModRef;

  return AAResultBase::getModRefInfo(CS, Loc);
}

getModRefBehavior(ImmutableCallSite CS) {
  if (CS.doesNotAccessMemory())

    return FMRB_DoesNotAccessMemory;

  FunctionModRefBehavior Min = FMRB_UnknownModRefBehavior;


  if (CS.onlyReadsMemory())
    Min = FMRB_OnlyReadsMemory;

  if (CS.onlyAccessesArgMemory())
    Min = FunctionModRefBehavior(Min & FMRB_OnlyAccessesArgumentPointees);


  return FunctionModRefBehavior(AAResultBase::getModRefBehavior(CS) & Min);
}

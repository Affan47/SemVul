getArgModRefInfo(ImmutableCallSite CS, unsigned ArgIdx) {
  ModRefInfo Result = MRI_ModRef;

  for (const auto &AA : AAs) {
    Result = ModRefInfo(Result & AA->getArgModRefInfo(CS, ArgIdx));


    if (Result == MRI_NoModRef)
      return Result;
  }

  return Result;
}

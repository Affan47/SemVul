useF32FTZ() const {
  if (FtzEnabled.getNumOccurrences() > 0) {

    return FtzEnabled;
  } else {
    const Function *F = MF->getFunction();

    if (F->hasFnAttribute("nvptx-f32ftz"))
      return F->getFnAttribute("nvptx-f32ftz").getValueAsString() == "true";
    else
      return false;
  }
}

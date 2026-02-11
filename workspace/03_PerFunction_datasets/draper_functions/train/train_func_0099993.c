CreateVariableSizedObject(unsigned Alignment,
                                                const AllocaInst *Alloca) {
  HasVarSizedObjects = true;
  Alignment = clampStackAlignment(!StackRealignable || !RealignOption,
                                  Alignment, StackAlignment);
  Objects.push_back(StackObject(0, Alignment, 0, false, false, Alloca, true));
  ensureMaxAlignment(Alignment);
  return (int)Objects.size()-NumFixedObjects-1;
}

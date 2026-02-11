getKnownConstant(Value *Val, ConstantPreference Preference) {
  if (!Val)
    return 0;


  if (UndefValue *U = dyn_cast<UndefValue>(Val))
    return U;

  if (Preference == WantBlockAddress)
    return dyn_cast<BlockAddress>(Val->stripPointerCasts());

  return dyn_cast<ConstantInt>(Val);
}

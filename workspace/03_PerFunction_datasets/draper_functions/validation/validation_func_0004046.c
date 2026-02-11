callIsSmall(const Function *F) {
  if (!F) return false;

  if (F->hasLocalLinkage()) return false;

  if (!F->hasName()) return false;

  StringRef Name = F->getName();


  if (Name == "copysign" || Name == "copysignf" || Name == "copysignl" ||
      Name == "fabs" || Name == "fabsf" || Name == "fabsl" ||
      Name == "sin" || Name == "sinf" || Name == "sinl" ||
      Name == "cos" || Name == "cosf" || Name == "cosl" ||
      Name == "sqrt" || Name == "sqrtf" || Name == "sqrtl" )
    return true;


  if (Name == "pow" || Name == "powf" || Name == "powl" ||
      Name == "exp2" || Name == "exp2l" || Name == "exp2f" ||
      Name == "floor" || Name == "floorf" || Name == "ceil" ||
      Name == "round" || Name == "ffs" || Name == "ffsl" ||
      Name == "abs" || Name == "labs" || Name == "llabs")
    return true;

  return false;
}

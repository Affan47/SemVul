GetBasicInstructionClass(const Value *V) {
  if (const CallInst *CI = dyn_cast<CallInst>(V)) {
    if (const Function *F = CI->getCalledFunction())
      return GetFunctionClass(F);

    return IC_CallOrUser;
  }


  return IC_User;
}

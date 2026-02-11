doInitialization(CallGraph &CG) {
  CA.setTargetData(getAnalysisIfAvailable<TargetData>());

  Module &M = CG.getModule();

  for (Module::iterator I = M.begin(), E = M.end();
       I != E; ++I)
    if (!I->isDeclaration() && I->hasFnAttr(Attribute::NoInline))
      NeverInline.insert(I);


  GlobalVariable *GV = M.getNamedGlobal("llvm.noinline");

  if (GV == 0)
    return false;


  if (!GV->hasDefinitiveInitializer())
    return false;

  const ConstantArray *InitList = dyn_cast<ConstantArray>(GV->getInitializer());

  if (InitList == 0)
    return false;


  for (unsigned i = 0, e = InitList->getNumOperands(); i != e; ++i) {


    const Constant *Elt = InitList->getOperand(i);

    if (const ConstantExpr *CE = dyn_cast<ConstantExpr>(Elt))
      if (CE->getOpcode() == Instruction::BitCast)
        Elt = CE->getOperand(0);


    if (const Function *F = dyn_cast<Function>(Elt))
      NeverInline.insert(F);
  }

  return false;
}

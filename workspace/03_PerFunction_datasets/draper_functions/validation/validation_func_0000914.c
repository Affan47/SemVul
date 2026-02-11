runOnFunction(Function &F) {
  TLI = &getAnalysis<TargetLibraryInfo>();

  if (Optimizations.empty())
    InitOptimizations();

  const TargetData *TD = getAnalysisIfAvailable<TargetData>();

  IRBuilder<> Builder(F.getContext());

  bool Changed = false;
  for (Function::iterator BB = F.begin(), E = F.end(); BB != E; ++BB) {
    for (BasicBlock::iterator I = BB->begin(), E = BB->end(); I != E; ) {

      CallInst *CI = dyn_cast<CallInst>(I++);
      if (!CI) continue;


      Function *Callee = CI->getCalledFunction();
      if (Callee == 0 || !Callee->isDeclaration() ||
          !(Callee->hasExternalLinkage() || Callee->hasDLLImportLinkage()))
        continue;


      LibCallOptimization *LCO = Optimizations.lookup(Callee->getName());
      if (!LCO) continue;


      Builder.SetInsertPoint(BB, I);


      Builder.SetCurrentDebugLocation(CI->getDebugLoc());


      Value *Result = LCO->OptimizeCall(CI, TD, TLI, Builder);
      if (Result == 0) continue;

      DEBUG(dbgs() << "SimplifyLibCalls simplified: " << *CI;
            dbgs() << "  into: " << *Result << "\n");


      Changed = true;
      ++NumSimplified;


      I = CI; ++I;

      if (CI != Result && !CI->use_empty()) {
        CI->replaceAllUsesWith(Result);
        if (!Result->hasName())
          Result->takeName(CI);
      }
      CI->eraseFromParent();
    }
  }
  return Changed;
}

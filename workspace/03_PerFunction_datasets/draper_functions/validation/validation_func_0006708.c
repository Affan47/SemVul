runOnFunction(Function &F) {
  DEBUG(dbgs() << "Jump threading on function '" << F.getName() << "'\n");
  TD = getAnalysisIfAvailable<TargetData>();
  LVI = &getAnalysis<LazyValueInfo>();

  FindLoopHeaders(F);

  bool Changed, EverChanged = false;
  do {
    Changed = false;
    for (Function::iterator I = F.begin(), E = F.end(); I != E;) {
      BasicBlock *BB = I;

      while (ProcessBlock(BB))
        Changed = true;

      ++I;


      if (pred_begin(BB) == pred_end(BB) &&
          BB != &BB->getParent()->getEntryBlock()) {
        DEBUG(dbgs() << "  JT: Deleting dead block '" << BB->getName()
              << "' with terminator: " << *BB->getTerminator() << '\n');
        LoopHeaders.erase(BB);
        LVI->eraseBlock(BB);
        DeleteDeadBlock(BB);
        Changed = true;
        continue;
      }

      BranchInst *BI = dyn_cast<BranchInst>(BB->getTerminator());


      if (BI && BI->isUnconditional() &&
          BB != &BB->getParent()->getEntryBlock() &&

          BB->getFirstNonPHIOrDbg()->isTerminator()) {


        bool ErasedFromLoopHeaders = LoopHeaders.erase(BB);
        BasicBlock *Succ = BI->getSuccessor(0);


        LVI->eraseBlock(BB);
        if (TryToSimplifyUncondBranchFromEmptyBlock(BB)) {
          Changed = true;


          BB = Succ;
        }

        if (ErasedFromLoopHeaders)
          LoopHeaders.insert(BB);
      }
    }
    EverChanged |= Changed;
  } while (Changed);

  LoopHeaders.clear();
  return EverChanged;
}

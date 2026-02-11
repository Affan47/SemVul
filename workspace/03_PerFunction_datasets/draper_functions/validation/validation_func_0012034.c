SimplifyFunction(Function *F) {
  bool MadeChange = false;
  for (Function::iterator BB = F->begin(), E = F->end(); BB != E; ++BB) {
    if (InvokeInst *II = dyn_cast<InvokeInst>(BB->getTerminator()))
      if (II->doesNotThrow()) {
        SmallVector<Value*, 8> Args(II->op_begin(), II->op_end() - 3);

        CallInst *Call = CallInst::Create(II->getCalledValue(), Args, "", II);
        Call->takeName(II);
        Call->setCallingConv(II->getCallingConv());
        Call->setAttributes(II->getAttributes());
        Call->setDebugLoc(II->getDebugLoc());


        II->replaceAllUsesWith(Call);
        BasicBlock *UnwindBlock = II->getUnwindDest();
        UnwindBlock->removePredecessor(II->getParent());


        BranchInst::Create(II->getNormalDest(), II);


        BB->getInstList().pop_back();


        if (pred_begin(UnwindBlock) == pred_end(UnwindBlock))
          DeleteBasicBlock(UnwindBlock);

        ++NumRemoved;
        MadeChange = true;
      }

    for (BasicBlock::iterator I = BB->begin(), E = BB->end(); I != E; )
      if (CallInst *CI = dyn_cast<CallInst>(I++))
        if (CI->doesNotReturn() && !isa<UnreachableInst>(I)) {


          BasicBlock *New = BB->splitBasicBlock(I);


          BB->getInstList().pop_back();
          new UnreachableInst(BB->getContext(), BB);

          DeleteBasicBlock(New);
          MadeChange = true;
          ++NumUnreach;
          break;
        }
  }

  return MadeChange;
}

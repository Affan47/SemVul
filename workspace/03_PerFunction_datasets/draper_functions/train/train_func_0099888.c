mayLoopAccessLocation(Value *Ptr, ModRefInfo Access, Loop *L,
                                  const SCEV *BECount, unsigned StoreSize,
                                  AliasAnalysis &AA,
                                  Instruction *IgnoredStore) {


  uint64_t AccessSize = MemoryLocation::UnknownSize;


  if (const SCEVConstant *BECst = dyn_cast<SCEVConstant>(BECount))
    AccessSize = (BECst->getValue()->getZExtValue() + 1) * StoreSize;


  MemoryLocation StoreLoc(Ptr, AccessSize);

  for (Loop::block_iterator BI = L->block_begin(), E = L->block_end(); BI != E;
       ++BI)
    for (BasicBlock::iterator I = (*BI)->begin(), E = (*BI)->end(); I != E; ++I)
      if (&*I != IgnoredStore && (AA.getModRefInfo(&*I, StoreLoc) & Access))
        return true;

  return false;
}

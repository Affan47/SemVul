PushLoopPHIs(const Loop *L, SmallVectorImpl<Instruction *> &Worklist) {
  BasicBlock *Header = L->getHeader();


  for (BasicBlock::iterator I = Header->begin();
       PHINode *PN = dyn_cast<PHINode>(I); ++I)
    Worklist.push_back(PN);
}

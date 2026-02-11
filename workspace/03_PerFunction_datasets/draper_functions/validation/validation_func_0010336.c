canInterchangeLoops(unsigned InnerLoopId,
                                                  unsigned OuterLoopId,
                                                  CharMatrix &DepMatrix) {

  if (!isLegalToInterChangeLoops(DepMatrix, InnerLoopId, OuterLoopId)) {
    DEBUG(dbgs() << "Failed interchange InnerLoopId = " << InnerLoopId
                 << "and OuterLoopId = " << OuterLoopId
                 << "due to dependence\n");
    return false;
  }


  BasicBlock *OuterLoopPreHeader = OuterLoop->getLoopPreheader();
  BasicBlock *InnerLoopPreHeader = InnerLoop->getLoopPreheader();


  if (!OuterLoopPreHeader || OuterLoopPreHeader == OuterLoop->getHeader() ||
      isa<PHINode>(OuterLoopPreHeader->begin()) ||
      !OuterLoopPreHeader->getUniquePredecessor()) {
    OuterLoopPreHeader = InsertPreheaderForLoop(OuterLoop, CurrentPass);
  }

  if (!InnerLoopPreHeader || InnerLoopPreHeader == InnerLoop->getHeader() ||
      InnerLoopPreHeader == OuterLoop->getHeader()) {
    InnerLoopPreHeader = InsertPreheaderForLoop(InnerLoop, CurrentPass);
  }


  if (currentLimitations()) {
    DEBUG(dbgs() << "Not legal because of current transform limitation\n");
    return false;
  }


  if (!tightlyNested(OuterLoop, InnerLoop)) {
    DEBUG(dbgs() << "Loops not tightly nested\n");
    return false;
  }

  return true;
}

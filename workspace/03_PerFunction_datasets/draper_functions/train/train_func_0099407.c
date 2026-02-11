getExact(BasicBlock *ExitingBlock,
                                             ScalarEvolution *SE) const {
  for (const ExitNotTakenInfo *ENT = &ExitNotTaken;
       ENT != 0; ENT = ENT->getNextExit()) {

    if (ENT->ExitingBlock == ExitingBlock)
      return ENT->ExactNotTaken;
  }
  return SE->getCouldNotCompute();
}

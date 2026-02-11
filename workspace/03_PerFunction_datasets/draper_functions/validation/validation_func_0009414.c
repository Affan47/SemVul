collectLoadMoveSet(BasicBlock &BB,
                     std::vector<Value *> &PairableInsts,
                     DenseMap<Value *, Value *> &ChosenPairs,
                     DenseMap<Value *, std::vector<Value *> > &LoadMoveSet,
                     DenseSet<ValuePair> &LoadMoveSetPairs) {
    for (std::vector<Value *>::iterator PI = PairableInsts.begin(),
         PIE = PairableInsts.end(); PI != PIE; ++PI) {
      DenseMap<Value *, Value *>::iterator P = ChosenPairs.find(*PI);
      if (P == ChosenPairs.end()) continue;

      Instruction *I = cast<Instruction>(P->first);
      collectPairLoadMoveSet(BB, ChosenPairs, LoadMoveSet,
                             LoadMoveSetPairs, I);
    }
  }

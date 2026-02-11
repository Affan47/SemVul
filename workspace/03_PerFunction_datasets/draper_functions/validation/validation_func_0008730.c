GetValueInMiddleOfBlock(BasicBlock *BB) {


  if (!HasValueForBlock(BB))
    return GetValueAtEndOfBlock(BB);


  SmallVector<std::pair<BasicBlock*, Value*>, 8> PredValues;
  Value *SingularValue = 0;


  if (PHINode *SomePhi = dyn_cast<PHINode>(BB->begin())) {
    for (unsigned i = 0, e = SomePhi->getNumIncomingValues(); i != e; ++i) {
      BasicBlock *PredBB = SomePhi->getIncomingBlock(i);
      Value *PredVal = GetValueAtEndOfBlock(PredBB);
      PredValues.push_back(std::make_pair(PredBB, PredVal));


      if (i == 0)
        SingularValue = PredVal;
      else if (PredVal != SingularValue)
        SingularValue = 0;
    }
  } else {
    bool isFirstPred = true;
    for (pred_iterator PI = pred_begin(BB), E = pred_end(BB); PI != E; ++PI) {
      BasicBlock *PredBB = *PI;
      Value *PredVal = GetValueAtEndOfBlock(PredBB);
      PredValues.push_back(std::make_pair(PredBB, PredVal));


      if (isFirstPred) {
        SingularValue = PredVal;
        isFirstPred = false;
      } else if (PredVal != SingularValue)
        SingularValue = 0;
    }
  }


  if (PredValues.empty())
    return UndefValue::get(ProtoType);


  if (SingularValue != 0)
    return SingularValue;


  if (isa<PHINode>(BB->begin())) {
    DenseMap<BasicBlock*, Value*> ValueMapping(PredValues.begin(),
                                               PredValues.end());
    PHINode *SomePHI;
    for (BasicBlock::iterator It = BB->begin();
         (SomePHI = dyn_cast<PHINode>(It)); ++It) {
      if (IsEquivalentPHI(SomePHI, ValueMapping))
        return SomePHI;
    }
  }


  PHINode *InsertedPHI = PHINode::Create(ProtoType, ProtoName, &BB->front());
  InsertedPHI->reserveOperandSpace(PredValues.size());


  for (unsigned i = 0, e = PredValues.size(); i != e; ++i)
    InsertedPHI->addIncoming(PredValues[i].second, PredValues[i].first);


  if (Value *ConstVal = InsertedPHI->hasConstantValue()) {
    InsertedPHI->eraseFromParent();
    return ConstVal;
  }


  if (InsertedPHIs) InsertedPHIs->push_back(InsertedPHI);

  DEBUG(dbgs() << "  Inserted PHI: " << *InsertedPHI << "\n");
  return InsertedPHI;
}

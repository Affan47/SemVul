GetValueAtEndOfBlockInternal(BasicBlock *BB) {
  AvailableValsTy &AvailableVals = getAvailableVals(AV);
  if (Value *V = AvailableVals[BB])
    return V;

  SSAUpdaterImpl<SSAUpdater> Impl(this, &AvailableVals, InsertedPHIs);
  return Impl.GetValue(BB);
}

MarkBlocksLiveIn(BasicBlock *BB,
                             SmallPtrSetImpl<BasicBlock *> &LiveBBs) {
  if (!LiveBBs.insert(BB).second)
    return;

  for (pred_iterator PI = pred_begin(BB), E = pred_end(BB); PI != E; ++PI)
    MarkBlocksLiveIn(*PI, LiveBBs);
}

setComplete()
{
  addBarrier();
  mutexPtr_ = 0;
  completeLimit_ = 0;
  completeLimitWithLocChunkAfter_ = 0;
  if (pendingData_ && tailPtr_)
    *tailPtr_ = pendingData_;
  tailPtr_ = 0;
  pendingData_ = 0;
  complete_ = 1;
  moreNodesCondition_.set();
}

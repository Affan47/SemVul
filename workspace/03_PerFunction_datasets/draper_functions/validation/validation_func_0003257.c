CloseLiveStream(void)
{
  mClient->Lock();

  if (mDemuxer)
  {
    mDemuxer->Close();
    delete mDemuxer;
    mDemuxer = NULL;
  }

  mClient->Unlock();
}

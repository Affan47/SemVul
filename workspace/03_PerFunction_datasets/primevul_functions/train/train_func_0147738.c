int64 KaxInternalBlock::GetFrameSize(size_t FrameNumber)
{
  int64 _Result = -1;

  if ( FrameNumber < SizeList.size()) {
    _Result = SizeList[FrameNumber];
  }

  return _Result;
}

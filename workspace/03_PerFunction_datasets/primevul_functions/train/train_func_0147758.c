bool KaxInternalBlock::AddFrame(const KaxTrackEntry & track, uint64 timecode, DataBuffer & buffer, LacingType lacing, bool invisible)
{
  SetValueIsSet();
  if (myBuffers.size() == 0) {

    Timecode = timecode;
    TrackNumber = track.TrackNumber();
    mInvisible = invisible;
    mLacing = lacing;
  }
  myBuffers.push_back(&buffer);


  if (myBuffers.size() >= 8 || lacing == LACING_NONE)
    return false;

  if (lacing == LACING_XIPH)


    return (buffer.Size() < 6*0xFF);
  else
    return true;
}

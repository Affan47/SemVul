bool EbmlMaster::VerifyChecksum() const
{
  if (!bChecksumUsed)
    return true;

  EbmlCrc32 aChecksum;


  MemIOCallback TmpBuf(GetSize() - 6);
  for (size_t Index = 0; Index < ElementList.size(); Index++) {
    (ElementList[Index])->Render(TmpBuf, true, false, true);
  }
  aChecksum.FillCRC32(TmpBuf.GetDataBuffer(), TmpBuf.GetDataBufferSize());
  return (aChecksum.GetCrc32() == Checksum.GetCrc32());
}

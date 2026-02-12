filepos_t EbmlMaster::ReadData(IOCallback & input, ScopeMode )
{
  input.setFilePointer(GetSize(), seek_current);
  return GetSize();
}

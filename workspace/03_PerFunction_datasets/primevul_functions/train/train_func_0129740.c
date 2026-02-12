EbmlMaster::~EbmlMaster()
{
  assert(!IsLocked());

  size_t Index;

  for (Index = 0; Index < ElementList.size(); Index++) {
    if (!(*ElementList[Index]).IsLocked())  {
      delete ElementList[Index];
    }
  }
}

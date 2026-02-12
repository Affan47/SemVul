EbmlElement *EbmlMaster::FindNextElt(const EbmlElement & PastElt) const
{
  size_t Index;

  for (Index = 0; Index < ElementList.size(); Index++) {
    if ((ElementList[Index]) == &PastElt) {

      Index++;
      break;
    }
  }

  while (Index < ElementList.size()) {
    if ((EbmlId)PastElt == (EbmlId)(*ElementList[Index]))
      return ElementList[Index];
    Index++;
  }

  return NULL;
}

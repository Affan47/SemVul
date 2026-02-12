EbmlElement * EbmlElement::FindNextID(IOCallback & DataStream, const EbmlCallbacks & ClassInfos, uint64 MaxDataSize)
{
  binary PossibleId[4];
  int PossibleID_Length = 0;
  binary PossibleSize[8];
  uint32 PossibleSizeLength = 0;
  uint64 SizeUnknown = 0;
  uint64 SizeFound = 0;
  bool bElementFound = false;

  binary BitMask;
  uint64 aElementPosition = 0, aSizePosition = 0;
  while (!bElementFound) {

    aElementPosition = DataStream.getFilePointer();
    uint32 ReadSize = 0;
    BitMask = 1 << 7;
    while (1) {
      ReadSize += DataStream.read(&PossibleId[PossibleID_Length], 1);
      if (ReadSize == uint32(PossibleID_Length)) {
        return NULL;
      }
      if (++PossibleID_Length > 4) {
        return NULL;
      }
      if (PossibleId[0] & BitMask) {


        bElementFound = true;
        break;
      }
      BitMask >>= 1;
    }


    aSizePosition = DataStream.getFilePointer();
    uint32 _SizeLength;
    do {
      if (PossibleSizeLength >= 8)

        return NULL;

      ReadSize += DataStream.read(&PossibleSize[PossibleSizeLength++], 1);
      _SizeLength = PossibleSizeLength;
      SizeFound = ReadCodedSizeValue(&PossibleSize[0], _SizeLength, SizeUnknown);
    } while (_SizeLength == 0);
  }

  EbmlElement *Result = NULL;
  EbmlId PossibleID(PossibleId, PossibleID_Length);
  if (PossibleID == EBML_INFO_ID(ClassInfos)) {

    Result = &EBML_INFO_CREATE(ClassInfos);
  } else {

    Result = new (std::nothrow) EbmlDummy(PossibleID);
    if(Result == NULL)
      return NULL;
  }

  Result->SetSizeLength(PossibleSizeLength);

  Result->Size = SizeFound;

  if (!Result->ValidateSize() || (SizeFound != SizeUnknown && MaxDataSize < Result->Size)) {
    delete Result;
    return NULL;
  }


  if (SizeFound == SizeUnknown) {


    if (!Result->SetSizeInfinite()) {

      delete Result;
      return NULL;
    }
  } else Result->SetSizeInfinite(false);
  Result->ElementPosition = aElementPosition;
  Result->SizePosition = aSizePosition;

  return Result;
}

EbmlElement * EbmlElement::FindNextElement(IOCallback & DataStream, const EbmlSemanticContext & Context, int & UpperLevel,
                                           uint64 MaxDataSize, bool AllowDummyElt, unsigned int MaxLowerLevel)
{
  int PossibleID_Length = 0;
  binary PossibleIdNSize[16];
  int PossibleSizeLength;
  uint64 SizeUnknown;
  int ReadIndex = 0;
  uint32 ReadSize = 0;
  uint64 SizeFound;
  int SizeIdx;
  bool bFound;
  int UpperLevel_original = UpperLevel;

  do {

    do {
      assert(ReadIndex < 16);

      bFound = false;
      binary IdBitMask = 1 << 7;
      for (SizeIdx = 0; SizeIdx < ReadIndex && SizeIdx < 4; SizeIdx++) {
        if (PossibleIdNSize[0] & (IdBitMask >> SizeIdx)) {

          PossibleID_Length = SizeIdx + 1;
          IdBitMask >>= SizeIdx;
          bFound = true;
          break;
        }
      }
      if (bFound) {
        break;
      }

      if (ReadIndex >= 4) {


        memmove(&PossibleIdNSize[0],&PossibleIdNSize[1], --ReadIndex);
      }

      if (DataStream.read(&PossibleIdNSize[ReadIndex++], 1) == 0) {
        return NULL;
      }
      ReadSize++;

    } while (!bFound && MaxDataSize > ReadSize);

    if (!bFound)

      return NULL;

    SizeIdx = ReadIndex;
    ReadIndex -= PossibleID_Length;


    uint32 _SizeLength;
    PossibleSizeLength = ReadIndex;
    while (1) {
      _SizeLength = PossibleSizeLength;
      SizeFound = ReadCodedSizeValue(&PossibleIdNSize[PossibleID_Length], _SizeLength, SizeUnknown);
      if (_SizeLength != 0) {
        bFound = true;
        break;
      }
      if (PossibleSizeLength >= 8) {
        bFound = false;
        break;
      }
      if( DataStream.read( &PossibleIdNSize[SizeIdx++], 1 ) == 0 ) {
        return NULL;
      }
      ReadSize++;
      PossibleSizeLength++;
    }

    if (bFound) {

      EbmlId PossibleID(PossibleIdNSize, PossibleID_Length);
      EbmlElement * Result = CreateElementUsingContext(PossibleID, Context, UpperLevel, false, AllowDummyElt, MaxLowerLevel);

      if (Result != NULL) {
        if (AllowDummyElt || !Result->IsDummy()) {
          Result->SetSizeLength(_SizeLength);

          Result->Size = SizeFound;


          if (Result->ValidateSize() && (SizeFound == SizeUnknown || UpperLevel > 0 || MaxDataSize == 0 || MaxDataSize >= (PossibleID_Length + PossibleSizeLength + SizeFound))) {
            if (SizeFound == SizeUnknown) {
              Result->SetSizeInfinite();
            }

            Result->SizePosition = DataStream.getFilePointer() - SizeIdx + EBML_ID_LENGTH(PossibleID);
            Result->ElementPosition = Result->SizePosition - EBML_ID_LENGTH(PossibleID);

            DataStream.setFilePointer(Result->SizePosition + _SizeLength);
            return Result;
          }
        }
        delete Result;
      }
    }


    ReadIndex = SizeIdx - 1;
    memmove(&PossibleIdNSize[0], &PossibleIdNSize[1], ReadIndex);
    UpperLevel = UpperLevel_original;
  } while ( MaxDataSize > DataStream.getFilePointer() - SizeIdx + PossibleID_Length );

  return NULL;
}

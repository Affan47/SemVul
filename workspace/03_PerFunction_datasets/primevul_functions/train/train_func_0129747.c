void EbmlMaster::Read(EbmlStream & inDataStream, const EbmlSemanticContext & sContext, int & UpperEltFound, EbmlElement * & FoundElt, bool AllowDummyElt, ScopeMode ReadFully)
{
  if (ReadFully == SCOPE_NO_DATA)
    return;

  EbmlElement * ElementLevelA;

  size_t Index;
  for (Index=0; Index<ElementList.size(); Index++) {
    if (!(*ElementList[Index]).IsLocked()) {
      delete ElementList[Index];
    }
  }
  ElementList.clear();
  uint64 MaxSizeToRead;

  if (IsFiniteSize())
    MaxSizeToRead = GetSize();
  else
    MaxSizeToRead = 0x7FFFFFFF;


  if (MaxSizeToRead > 0)
  {
    inDataStream.I_O().setFilePointer(GetSizePosition() + GetSizeLength(), seek_beginning);
    ElementLevelA = inDataStream.FindNextElement(sContext, UpperEltFound, MaxSizeToRead, AllowDummyElt);
    while (ElementLevelA != NULL && UpperEltFound <= 0 && MaxSizeToRead > 0) {
      if (IsFiniteSize() && ElementLevelA->IsFiniteSize())
        MaxSizeToRead = GetEndPosition() - ElementLevelA->GetEndPosition();
      if (!AllowDummyElt && ElementLevelA->IsDummy()) {
        if (ElementLevelA->IsFiniteSize()) {
          ElementLevelA->SkipData(inDataStream, sContext);
          delete ElementLevelA;
        } else {
          delete ElementLevelA;
          break;
        }
      } else {
        ElementLevelA->Read(inDataStream, EBML_CONTEXT(ElementLevelA), UpperEltFound, FoundElt, AllowDummyElt, ReadFully);


        bool DeleteElement = true;

        if (ElementLevelA->ValueIsSet() || (ReadFully != SCOPE_ALL_DATA)) {
          ElementList.push_back(ElementLevelA);
          DeleteElement = false;
        }


        if (ElementLevelA->IsFiniteSize()) {
          ElementLevelA->SkipData(inDataStream, EBML_CONTEXT(ElementLevelA));
          if (DeleteElement)
            delete ElementLevelA;
        } else {
          if (DeleteElement)
            delete ElementLevelA;

          if (UpperEltFound) {
            --UpperEltFound;
            if (UpperEltFound > 0 || MaxSizeToRead <= 0)
              goto processCrc;
            ElementLevelA = FoundElt;
          }

          break;
        }
      }

      if (UpperEltFound > 0) {
        UpperEltFound--;
        if (UpperEltFound > 0 || MaxSizeToRead <= 0)
          goto processCrc;
        ElementLevelA = FoundElt;
        continue;
      }

      if (UpperEltFound < 0) {
        UpperEltFound++;
        if (UpperEltFound < 0)
          goto processCrc;
      }

      if (MaxSizeToRead <= 0)
        goto processCrc;

      ElementLevelA = inDataStream.FindNextElement(sContext, UpperEltFound, MaxSizeToRead, AllowDummyElt);
    }
    if (UpperEltFound > 0) {
      FoundElt = ElementLevelA;
    }
  }
processCrc:

  EBML_MASTER_ITERATOR Itr, CrcItr;
  for (Itr = ElementList.begin(); Itr != ElementList.end();) {
    if ((EbmlId)(*(*Itr)) == EBML_ID(EbmlCrc32)) {
      bChecksumUsed = true;

      Checksum = *(static_cast<EbmlCrc32*>(*Itr));
      CrcItr = Itr;
      break;
    }
    ++Itr;
  }

  if (bChecksumUsed)
  {
    delete *CrcItr;
    Remove(CrcItr);
  }

  SetValueIsSet();
}

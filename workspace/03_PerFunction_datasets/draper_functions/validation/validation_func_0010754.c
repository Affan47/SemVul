InitCellInsertion()
  {


    for(int i=0; i < LSDynaMetaData::NUM_CELL_TYPES; ++i)
      {
      if(this->Info[i].size()>0)
        {
        PartInsertion partIt(&this->Info[i]);
        this->CellInsertionIterators[i] = partIt;
        }
      }
  }

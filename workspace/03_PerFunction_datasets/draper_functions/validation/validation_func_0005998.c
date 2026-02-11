operator++()
    {
      this->Current += this->CurrentPolygonSize + 1;
      this->Id++;
      if (this->Id < this->NumberOfPolygons)
        {
        this->CurrentPolygonSize = *(this->Current-1);
        }
      else
        {
        this->CurrentPolygonSize = VTK_LARGE_ID;
        }
      return this->Current;
    }

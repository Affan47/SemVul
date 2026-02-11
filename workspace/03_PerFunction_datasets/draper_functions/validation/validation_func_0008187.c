AllocateExtents()
{
  int extent[6];
  this->GetExtent(extent);
  int ySize = (extent[3] - extent[2] + 1);
  int zSize = (extent[5] - extent[4] + 1);

  int numEntries = ySize*zSize;
  if (numEntries != this->NumberOfExtentEntries)
    {
    if (this->NumberOfExtentEntries != 0)
      {
      int n = this->NumberOfExtentEntries;
      for (int i = 0; i < n; i++)
        {
        if (this->ExtentLists[i] != &this->ExtentListLengths[n + 2*i])
          {
          delete [] this->ExtentLists[i];
          }
        }
      delete [] this->ExtentLists;
      delete [] this->ExtentListLengths;
      }

    this->NumberOfExtentEntries = numEntries;
    this->ExtentLists = NULL;
    this->ExtentListLengths = NULL;

    if (numEntries)
      {


      this->ExtentLists = new int *[numEntries];
      this->ExtentListLengths = new int[3*numEntries];
      for (int i = 0; i < numEntries; i++)
        {
        this->ExtentListLengths[i] = 0;
        this->ExtentLists[i] = &this->ExtentListLengths[numEntries + 2*i];
        }
      }
    }
  else
    {
    for (int i = 0; i < numEntries; i++)
      {
      if (this->ExtentLists[i] != &this->ExtentListLengths[numEntries + 2*i])
        {
        delete [] this->ExtentLists[i];
        }
      this->ExtentLists[i] = &this->ExtentListLengths[numEntries + 2*i];
      this->ExtentListLengths[i] = 0;
      }
    }
}

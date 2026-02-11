ShouldReadDataSet(unsigned int dataSetIndex)
{
  bool shouldRead =
    (dataSetIndex >= this->Internal->MinDataset &&
     dataSetIndex < this->Internal->MaxDataset);

  if (shouldRead && this->Internal->HasUpdateRestriction)
    {
    if (this->Internal->UpdateIndices.find(dataSetIndex) ==
        this->Internal->UpdateIndices.end())
      {
      shouldRead = false;
      }
    }
  return shouldRead;
}

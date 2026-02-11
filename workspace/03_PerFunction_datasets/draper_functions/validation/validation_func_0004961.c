RequestInformation(
  vtkInformation *vtkNotUsed(request),
  vtkInformationVector **vtkNotUsed(inputVector),
  vtkInformationVector *outputVector)
{
  vtkDebugMacro("In execute information");
  this->CaseFileRead = this->ReadCaseFile();


  std::vector<double> timeValues;
  if (this->GetTimeSets())
    {
    int numItems = this->GetTimeSets()->GetNumberOfItems();
    for (int i=0; i<numItems; i++)
      {
      vtkDataArray* array = this->GetTimeSets()->GetItem(i);
      if (array)
        {
        vtkIdType numTuples = array->GetNumberOfTuples();
        for (vtkIdType j=0; j<numTuples; j++)
          {
          timeValues.push_back(array->GetComponent(j, 0));
          }
        }
      }
    }
  if (timeValues.size() > 0)
    {
    std::sort(timeValues.begin(), timeValues.end());
    std::vector<double> uniqueTimeValues(
      timeValues.begin(),
      std::unique(timeValues.begin(), timeValues.end()));
    int numTimeValues = static_cast<int>(uniqueTimeValues.size());
    if (numTimeValues > 0)
      {
      vtkInformation* outInfo = outputVector->GetInformationObject(0);
      outInfo->Set(vtkStreamingDemandDrivenPipeline::TIME_STEPS(),
                   &uniqueTimeValues[0],
                   numTimeValues);
      double timeRange[2];
      timeRange[0] = uniqueTimeValues[0];
      timeRange[1] = uniqueTimeValues[numTimeValues-1];
      outInfo->Set(vtkStreamingDemandDrivenPipeline::TIME_RANGE(),
                   timeRange, 2);
      }
    }
  return this->CaseFileRead;
}

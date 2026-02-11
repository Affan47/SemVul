InitializeSeeds(vtkDataArray*& seeds,
                                                        vtkIdList*& seedIds,
                                                        vtkDoubleArray*& startTimes,
                                                        vtkIntArray*& integrationDirections,
                                                        vtkDataSet *source)
{
  this->Superclass::InitializeSeeds(seeds,seedIds,integrationDirections,source);

  startTimes = vtkDoubleArray::New();

  if (!source)
    {
    return;
    }

  vtkDataArray* sourceSeedTimes = source->GetPointData()->GetArray(this->SeedTimesArrayName);

  if (sourceSeedTimes)
    {
    startTimes->DeepCopy(sourceSeedTimes);
    }
  else
    {
    startTimes->SetNumberOfTuples(source->GetNumberOfPoints());
    startTimes->FillComponent(0,this->SeedTime);
    }
}

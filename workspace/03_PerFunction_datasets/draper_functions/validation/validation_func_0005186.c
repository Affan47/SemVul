BuildLabels()
{
  vtkDebugMacro(<<"Rebuilding labels");
  vtkDataObject* inputDO = this->GetInputDataObject(0, 0);
  vtkCompositeDataSet* cd = vtkCompositeDataSet::SafeDownCast(inputDO);
  vtkDataSet* ds = vtkDataSet::SafeDownCast(inputDO);
  if (ds)
    {
    this->AllocateLabels(ds->GetNumberOfPoints());
    this->NumberOfLabels = 0;
    this->BuildLabelsInternal(ds);
    }
  else if (cd)
    {
    this->AllocateLabels(cd->GetNumberOfPoints());
    this->NumberOfLabels = 0;
    vtkCompositeDataIterator* iter = cd->NewIterator();
    for (iter->InitTraversal(); !iter->IsDoneWithTraversal();
      iter->GoToNextItem())
      {
      ds = vtkDataSet::SafeDownCast(iter->GetCurrentDataObject());
      if (ds)
        {
        this->BuildLabelsInternal(ds);
        }
      }
    iter->Delete();
    }
  else
    {
    vtkErrorMacro("Unsupported data type: " << inputDO->GetClassName());
    }

  this->BuildTime.Modified();
}

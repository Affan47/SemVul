Initialize()
{


  this->GetPolyDataInput(0)->Update();

  vtkIdType numCells = this->GetPolyDataInput(0)->GetNumberOfCells();
  this->CellIdList->SetNumberOfIds(numCells);

  for (vtkIdType i=0; i < numCells; i++)
    {
    this->CellIdList->SetId(i,i);
    }

  this->IsInitialized = 1;
}

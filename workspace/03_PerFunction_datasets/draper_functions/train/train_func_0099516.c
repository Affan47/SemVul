AddCellList(vtkIdList *l)
{
  if (l == NULL)
    {
    return;
    }

  vtkIdType ncells = l->GetNumberOfIds();

  if (ncells == 0)
    {
    return;
    }

  for (int i=0; i<ncells; i++)
    {
    this->CellList->IdTypeSet.insert(l->GetId(i));
    }

  this->Modified();

  return;
}

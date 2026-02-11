AddArray(vtkAbstractArray *array)
{
  if (!array)
    {
    return -1;
    }

  int index;
  this->GetAbstractArray(array->GetName(), index);

  if (index == -1)
    {
    index = this->NumberOfActiveArrays;
    this->NumberOfActiveArrays++;
    }
  this->SetArray(index, array);
  return index;
}

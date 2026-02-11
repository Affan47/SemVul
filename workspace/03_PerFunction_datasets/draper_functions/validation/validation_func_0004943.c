IsInside(vtkIdType inputPtId)
{
  if ( !this->InsideOutsideArray ||
       this->InsideOutsideArray->GetValue(inputPtId) == 0 )
    {
    return 0;
    }
  else
    {
    return 1;
    }
}

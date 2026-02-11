InputFieldsAreValid
(int port, vtkInformationVector **inInfoVec)
{

  if (!inInfoVec[port])
    {
    return 0;
    }
  int result = 1;
  for(int i=0; i < inInfoVec[port]->GetNumberOfInformationObjects(); ++i)
    {
    if(!this->InputFieldsAreValid(port, i, inInfoVec))
      {
      result = 0;
      }
    }
  return result;
}

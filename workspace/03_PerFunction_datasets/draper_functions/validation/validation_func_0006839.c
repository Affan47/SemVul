RequestInformation(vtkInformation*,
                                           vtkInformationVector**,
                                           vtkInformationVector* outputVector)
{

  if(this->OutputScalarType != -1)
    {
    vtkInformation* outInfo = outputVector->GetInformationObject(0);
    vtkDataObject::SetPointDataActiveScalarInfo(
      outInfo, this->OutputScalarType, -1);
    }
  return 1;
}

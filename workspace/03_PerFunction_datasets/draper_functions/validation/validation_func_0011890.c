ShouldIReleaseData()
{
  return vtkDataObjectGlobalReleaseDataFlag || this->GetReleaseDataFlag();
}

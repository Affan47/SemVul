SetAlgorithm(vtkAlgorithm* newAlgorithm)
{
  vtkDebugMacro(<< this->GetClassName() << " (" << this
                << "): setting Algorithm to " << newAlgorithm);
  vtkAlgorithm* oldAlgorithm = this->Algorithm;
  if(oldAlgorithm != newAlgorithm)
    {
    if(newAlgorithm)
      {
      newAlgorithm->Register(this);
      }
    this->Algorithm = newAlgorithm;
    if(oldAlgorithm)
      {
      oldAlgorithm->UnRegister(this);
      }
    this->Modified();
    }
}

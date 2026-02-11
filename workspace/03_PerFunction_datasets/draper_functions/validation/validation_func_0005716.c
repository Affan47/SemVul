MeshUpToDate()
{
  if (this->MeshReadTime < this->GetMTime())
    {
    return 0;
    }
  if (this->MeshReadTime < this->Internal->VariableArraySelection->GetMTime())
    {
    return 0;
    }
  return 1;
}

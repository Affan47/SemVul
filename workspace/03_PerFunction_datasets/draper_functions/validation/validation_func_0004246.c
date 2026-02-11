GetBounds()
{
  vtkDataSet *input = this->GetInput();
  if ( ! input )
    {
      vtkMath::UninitializeBounds(this->Bounds);
    }
  else
    {
    if (!this->Static)
      {
      this->Update();
      }
    input->GetBounds(this->Bounds);
    }
  return this->Bounds;
}

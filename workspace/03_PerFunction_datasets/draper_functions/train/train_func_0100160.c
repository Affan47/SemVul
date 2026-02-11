FillPixel(int x, int y)
{
  void *ptr;
  int *ext = this->ImageData->GetExtent();
  int z = this->DefaultZ;


  if (this->Ratio[0] != 1.0)
    {
    x = static_cast<int>(static_cast<double>(x) * this->Ratio[0]);
    }
  if (this->Ratio[1] != 1.0)
    {
    y = static_cast<int>(static_cast<double>(y) * this->Ratio[1]);
    }
  if (this->Ratio[2] != 1.0)
    {
    z = static_cast<int>(static_cast<double>(z) * this->Ratio[2]);
    }

  z = (z < ext[4]) ? ext[4] : z;
  z = (z > ext[5]) ? ext[5] : z;

  ptr = this->ImageData->GetScalarPointer(x, y, z);

  switch (this->ImageData->GetScalarType())
    {
    vtkTemplateMacro(
      vtkImageCanvasSource2DFill(this->ImageData,
                                 this->DrawColor,
                                 static_cast<VTK_TT *>(ptr),
                                 x, y));
    default:
      vtkErrorMacro(<< "Fill: Cannot handle ScalarType.");
    }
  this->Modified();
}

SetScalarComponentFromDouble(int x, int y, int z, int comp,
                                                double value)
{

  if(comp < 0 || comp >= this->GetNumberOfScalarComponents())
    {
    vtkErrorMacro("Bad component index " << comp);
    return;
    }


  void* ptr = this->GetScalarPointer(x, y, z);
  if(!ptr)
    {

    return;
    }


  switch (this->GetScalarType())
    {
    vtkTemplateMacro(vtkImageDataConvertScalar(
                       &value, static_cast<VTK_TT*>(ptr)+comp));
    default:
      {
      vtkErrorMacro("Unknown Scalar type " << this->GetScalarType());
      }
    }
}

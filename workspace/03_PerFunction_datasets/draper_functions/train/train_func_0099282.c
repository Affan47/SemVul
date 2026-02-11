PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);

  if ( this->Input )
    {
    os << indent << "Input:\n";
    this->Input->PrintSelf(os,indent.GetNextIndent());
    }
  else
    {
    os << indent << "Input: (none)\n";
    }
  os << indent << "ReadFrontBuffer: " << this->ReadFrontBuffer << "\n";
  os << indent << "Magnification: " << this->Magnification << "\n";
  os << indent << "ShouldRerender: " << this->ShouldRerender << "\n";
  os << indent << "Viewport: " << this->Viewport[0] << "," << this->Viewport[1]
     << "," << this->Viewport[2] << "," << this->Viewport[3] << "\n";
  os << indent << "InputBufferType: " << this->InputBufferType << "\n";
  os << indent << "FixBoundary: " << this->FixBoundary << endl;
}

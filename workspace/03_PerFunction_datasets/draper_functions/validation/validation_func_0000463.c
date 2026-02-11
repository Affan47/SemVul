PrintSelf(ostream& os, vtkIndent indent)
{

  this->Superclass::PrintSelf(os,indent);

  os << indent << "Render Window Interactor: ";
  if ( this->Interactor )
    {
    os << this->Interactor << "\n";
    }
  else
    {
    os << "(None)\n";
    }

}

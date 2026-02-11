PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);

  os << indent << "File Name: "
     << (this->FileName ? this->FileName : "(none)") << "\n";

  os << indent << "Number Of Nodes: " << this->NumberOfNodes << endl;
  os << indent << "Number Of Node Fields: "
     << this->NumberOfNodeFields << endl;

  os << indent << "Number Of Cells: " << this->NumberOfCells << endl;
  os << indent << "Number Of Cell Fields: "
     << this->NumberOfCellFields << endl;
}

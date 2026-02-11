WriteCellsAppended(const char* name,
                                                      vtkDataArray* types,
                                                      vtkIndent indent,
                                                      OffsetsManagerGroup *cellsManager)
{
  ostream& os = *(this->Stream);
  os << indent << "<" << name << ">\n";


  vtkDataArray *allcells[5];
  allcells[0] = this->CellPoints;
  allcells[1] = this->CellOffsets;
  allcells[2] = types;
  allcells[3] = this->Faces->GetNumberOfTuples() ? this->Faces : 0;
  allcells[4] = this->FaceOffsets->GetNumberOfTuples() ? this->FaceOffsets : 0;
  const char *names[] = {NULL, NULL, "types", NULL, NULL};

  for(int t=0; t<this->NumberOfTimeSteps; t++)
    {
    for(int i=0; i<5; i++)
      {
      if(allcells[i])
        {
        this->WriteArrayAppended(allcells[i], indent.GetNextIndent(),
          cellsManager->GetElement(i), names[i], 0, t);
        if (this->ErrorCode == vtkErrorCode::OutOfDiskSpaceError)
          {
          return;
          }
        }
      }
    }
  os << indent << "</" << name << ">\n";
  os.flush();
  if (os.fail())
    {
    this->SetErrorCode(vtkErrorCode::OutOfDiskSpaceError);
    return;
    }

}

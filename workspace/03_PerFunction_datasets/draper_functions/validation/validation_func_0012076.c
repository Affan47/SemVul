WriteAppendedPieceData(int index)
{
  ostream& os = *(this->Stream);
  vtkUnstructuredGrid* input = this->GetInput();

  unsigned long returnPosition = os.tellp();
  os.seekp(this->NumberOfCellsPositions[index]);
  this->WriteScalarAttribute("NumberOfCells", input->GetNumberOfCells());
  if (this->ErrorCode == vtkErrorCode::OutOfDiskSpaceError)
    {
    return;
    }
  os.seekp(returnPosition);


  float progressRange[2] = {0,0};
  this->GetProgressRange(progressRange);
  float fractions[3];
  this->CalculateSuperclassFraction(fractions);


  this->SetProgressRange(progressRange, 0, fractions);


  this->Superclass::WriteAppendedPieceData(index);
  if (this->ErrorCode == vtkErrorCode::OutOfDiskSpaceError)
    {
    return;
    }


  this->SetProgressRange(progressRange, 1, fractions);


  this->WriteCellsAppendedData( input->GetCells(),
    input->GetCellTypesArray(), input->GetFaces(),
    input->GetFaceLocations(), this->CurrentTimeIndex,
    &this->CellsOM->GetPiece(index));
}

ReadXMLData()
{

  int piece;
  int numberOfPieces;
  int ghostLevel;
  vtkInformation* outInfo = this->GetCurrentOutputInformation();
  piece = outInfo->Get(
      vtkStreamingDemandDrivenPipeline::UPDATE_PIECE_NUMBER());
  numberOfPieces = outInfo->Get(
      vtkStreamingDemandDrivenPipeline::UPDATE_NUMBER_OF_PIECES());
  ghostLevel = outInfo->Get(
      vtkStreamingDemandDrivenPipeline::UPDATE_NUMBER_OF_GHOST_LEVELS());

  vtkDebugMacro("Updating piece " << piece << " of " << numberOfPieces
                << " with ghost level " << ghostLevel);


  this->SetupUpdateExtent(piece, numberOfPieces, ghostLevel);


  if(this->StartPiece == this->EndPiece)
    {
    return;
    }

  vtkDebugMacro("Reading piece range [" << this->StartPiece
                << ", " << this->EndPiece << ") from file.");


  this->Superclass::ReadXMLData();


  float progressRange[2] = {0,0};
  this->GetProgressRange(progressRange);


  float* fractions = new float[this->EndPiece-this->StartPiece+1];
  int i;
  fractions[0] = 0;
  for(i=this->StartPiece; i < this->EndPiece; ++i)
    {
    int index = i-this->StartPiece;
    fractions[index+1] = (fractions[index] +
                          this->GetNumberOfPointsInPiece(i) +
                          this->GetNumberOfCellsInPiece(i));
    }
  if(fractions[this->EndPiece-this->StartPiece] == 0)
    {
    fractions[this->EndPiece-this->StartPiece] = 1;
    }
  for(i=this->StartPiece; i < this->EndPiece; ++i)
    {
    int index = i-this->StartPiece;
    fractions[index+1] = fractions[index+1] / fractions[this->EndPiece-this->StartPiece];
    }


  for(i=this->StartPiece; (i < this->EndPiece && !this->AbortExecute &&
                           !this->DataError); ++i)
    {

    this->SetProgressRange(progressRange, i-this->StartPiece, fractions);

    if(!this->Superclass::ReadPieceData(i))
      {

      this->DataError = 1;
      }
    this->SetupNextPiece();
    }

  delete [] fractions;
}

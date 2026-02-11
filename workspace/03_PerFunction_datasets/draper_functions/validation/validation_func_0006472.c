Reset()
{
  if ( ! VTK_LSDYNA_ISBADFILE(this->FD) )
    {
    VTK_LSDYNA_CLOSEFILE(this->FD);
    this->FD = VTK_LSDYNA_BADFILE;
    }

  this->DatabaseDirectory = "";
  this->DatabaseBaseName = "";
  this->Files.clear();
  this->FileSizes.clear();
  this->Adaptations.clear();
  this->FileAdaptLevels.clear();
  this->TimeStepMarks.clear();
  this->TimeAdaptLevels.clear();
  this->FNum = -1;
  this->FAdapt = -1;
  this->FWord = 0;
  this->TimeStep = -1;
  this->ChunkValid = 0;
  this->FileHandlesClosed = false;

  delete this->BufferInfo;
  this->BufferInfo = new LSDynaFamily::BufferingInfo();
}

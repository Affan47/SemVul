SetExportFile(const char* mainFile)
{
  this->MainImportFile = mainFile;
  this->FileDir =
    cmSystemTools::GetFilenamePath(this->MainImportFile);
  this->FileBase =
    cmSystemTools::GetFilenameWithoutLastExtension(this->MainImportFile);
  this->FileExt =
    cmSystemTools::GetFilenameLastExtension(this->MainImportFile);
}

SubmitExtraFiles(const std::vector<cmStdString> &files)
{
  std::vector<cmStdString>::const_iterator it;
  for ( it = files.begin();
    it != files.end();
    ++ it )
    {
    if ( !cmSystemTools::FileExists(it->c_str()) )
      {
      cmCTestLog(this, ERROR_MESSAGE, "Cannot find extra file: "
        << it->c_str() << " to submit."
        << std::endl;);
      return false;
      }
    this->AddSubmitFile(PartExtraFiles, it->c_str());
    }
  return true;
}

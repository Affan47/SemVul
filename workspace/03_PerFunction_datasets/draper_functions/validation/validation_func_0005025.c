StartResultingXML(cmCTest::Part part,
                                              const char* name,
                                              cmGeneratedFileStream& xofs)
{
  if ( !name )
    {
    cmCTestLog(this->CTest, ERROR_MESSAGE,
      "Cannot create resulting XML file without providing the name"
      << std::endl;);
    return false;
    }
  cmOStringStream ostr;
  ostr << name;
  if ( this->SubmitIndex > 0 )
    {
    ostr << "_" << this->SubmitIndex;
    }
  ostr << ".xml";
  if(this->CTest->GetCurrentTag().empty())
    {
    cmCTestLog(this->CTest, ERROR_MESSAGE,
               "Current Tag empty, this may mean NightlyStartTime / "
               "CTEST_NIGHTLY_START_TIME was not set correctly. Or "
               "maybe you forgot to call ctest_start() before calling "
               "ctest_configure()." << std::endl);
    cmSystemTools::SetFatalErrorOccured();
    return false;
    }
  if( !this->CTest->OpenOutputFile(this->CTest->GetCurrentTag(),
      ostr.str().c_str(), xofs, true) )
    {
    cmCTestLog(this->CTest, ERROR_MESSAGE,
      "Cannot create resulting XML file: " << ostr.str().c_str()
      << std::endl);
    return false;
    }
  this->CTest->AddSubmitFile(part, ostr.str().c_str());
  return true;
}

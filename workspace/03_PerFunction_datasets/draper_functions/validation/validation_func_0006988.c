ReadInScript(const std::string& total_script_arg)
{

  cmSystemTools::ResetErrorOccuredFlag();


  std::string script = total_script_arg;
  std::string script_arg;
  if (total_script_arg.find(",") != std::string::npos)
    {
    script = total_script_arg.substr(0,total_script_arg.find(","));
    script_arg = total_script_arg.substr(total_script_arg.find(",")+1);
    }

  if (!cmSystemTools::FileExists(script.c_str()))
    {
    cmSystemTools::Error("Cannot find file: ", script.c_str());
    return 1;
    }


  this->CreateCMake();


  this->Makefile->AddDefinition("CTEST_SCRIPT_DIRECTORY",
                            cmSystemTools::GetFilenamePath(script).c_str());
  this->Makefile->AddDefinition("CTEST_SCRIPT_NAME",
                            cmSystemTools::GetFilenameName(script).c_str());
  this->Makefile->AddDefinition("CTEST_EXECUTABLE_NAME",
                            this->CTest->GetCTestExecutable());
  this->Makefile->AddDefinition("CMAKE_EXECUTABLE_NAME",
                            this->CTest->GetCMakeExecutable());
  this->Makefile->AddDefinition("CTEST_RUN_CURRENT_SCRIPT", true);
  this->UpdateElapsedTime();


  if (script_arg.size())
    {
    this->Makefile->AddDefinition("CTEST_SCRIPT_ARG", script_arg.c_str());
    }


  cmCTestScriptFunctionBlocker *f = new cmCTestScriptFunctionBlocker();
  f->CTestScriptHandler = this;
  this->Makefile->AddFunctionBlocker(f);


  std::string systemFile =
      this->Makefile->GetModulesFile("CTestScriptMode.cmake");
  if (!this->Makefile->ReadListFile(0, systemFile.c_str()) ||
      cmSystemTools::GetErrorOccuredFlag())
    {
    cmCTestLog(this->CTest, ERROR_MESSAGE, "Error in read:"
               << systemFile.c_str() << "\n");
    return 2;
    }


  const std::map<std::string, std::string> &defs =
    this->CTest->GetDefinitions();
  for (std::map<std::string, std::string>::const_iterator it = defs.begin();
       it != defs.end(); ++it)
    {
    this->Makefile->AddDefinition(it->first.c_str(), it->second.c_str());
    }


  if (!this->Makefile->ReadListFile(0, script.c_str()) ||
    cmSystemTools::GetErrorOccuredFlag())
    {
    cmCTestLog(this->CTest, ERROR_MESSAGE, "Error in read script: "
               << script.c_str()
               << std::endl);


    cmSystemTools::ResetErrorOccuredFlag();
    return 2;
    }

  return 0;
}

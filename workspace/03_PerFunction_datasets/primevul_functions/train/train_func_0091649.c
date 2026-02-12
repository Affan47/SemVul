void __fastcall TSCPFileSystem::DoStartup()
{

  FTerminal->SaveCapabilities(FFileSystemInfo);


  try
  {
    FTerminal->ExceptionOnFail = true;
    SkipStartupMessage();
    if (FTerminal->SessionData->DetectReturnVar) DetectReturnVar();
    FTerminal->ExceptionOnFail = false;
  }
  catch (Exception & E)
  {
    FTerminal->FatalError(&E, L"");
  }


  DetectUtf();

  #define COND_OPER(OPER) if (FTerminal->SessionData->OPER) OPER()
  COND_OPER(ClearAliases);
  COND_OPER(UnsetNationalVars);
  #undef COND_OPER
}

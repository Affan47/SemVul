void __fastcall TSCPFileSystem::CopyFile(const UnicodeString FileName, const TRemoteFile * ,
  const UnicodeString NewName)
{
  UnicodeString DelimitedFileName = DelimitStr(FileName);
  UnicodeString DelimitedNewName = DelimitStr(NewName);
  const UnicodeString AdditionalSwitches = L"-T";
  try
  {
    ExecCommand(fsCopyFile, ARRAYOFCONST((AdditionalSwitches, DelimitedFileName, DelimitedNewName)));
  }
  catch (Exception & E)
  {
    if (FTerminal->Active)
    {


      FTerminal->LogEvent(FORMAT(L"Attempt with %s failed, trying without", (AdditionalSwitches)));
      ExecCommand(fsCopyFile, ARRAYOFCONST((L"", DelimitedFileName, DelimitedNewName)));
    }
    else
    {
      throw;
    }
  }
}

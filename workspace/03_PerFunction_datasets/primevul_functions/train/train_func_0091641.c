void __fastcall TSCPFileSystem::CreateDirectory(const UnicodeString & DirName, bool )
{
  ExecCommand(fsCreateDirectory, ARRAYOFCONST((DelimitStr(DirName))));
}

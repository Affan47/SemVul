void __fastcall TSCPFileSystem::RenameFile(const UnicodeString FileName, const TRemoteFile * ,
  const UnicodeString NewName)
{
  ExecCommand(fsRenameFile, ARRAYOFCONST((DelimitStr(FileName), DelimitStr(NewName))));
}

void __fastcall TSCPFileSystem::ClearAlias(UnicodeString Alias)
{
  if (!Alias.IsEmpty())
  {


    ExecCommand(fsUnalias, ARRAYOFCONST((Alias)), false);
  }
}

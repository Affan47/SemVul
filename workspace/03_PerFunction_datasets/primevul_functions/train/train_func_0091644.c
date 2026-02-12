UnicodeString __fastcall TSCPFileSystem::AbsolutePath(UnicodeString Path, bool )
{
  return ::AbsolutePath(CurrentDirectory, Path);
}

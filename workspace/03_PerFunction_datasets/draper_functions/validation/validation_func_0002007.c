TempDir()
{
   return FileNames::MkDir(gPrefs->Read(wxT("/Directories/TempDir"), wxT("")));
}

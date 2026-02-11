GetFileBase(const char *f)
{
	FileBaseInfo fbi = DetermineFileBase(f);
	strcpy(FileBase,fbi.filebase.c_str());
	strcpy(FileBaseDirectory,fbi.filebasedirectory.c_str());
}

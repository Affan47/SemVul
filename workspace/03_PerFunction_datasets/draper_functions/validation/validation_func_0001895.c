SetFileUrl(const fstring& filename)
{
	fileManager->PopRootFile();
	fileUrl = GetFileManager()->GetCurrentUri().MakeAbsolute(filename);
	fileManager->PushRootFile(fileUrl);
}

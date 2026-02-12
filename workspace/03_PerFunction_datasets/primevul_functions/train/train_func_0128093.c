void LibRaw_windows_datastream::Open(HANDLE hFile)
{

  hMap_ = ::CreateFileMapping(hFile, 0, PAGE_READONLY, 0, 0, 0);
  if (hMap_ == NULL)
    throw std::runtime_error("failed to create file mapping");


  if (!::GetFileSizeEx(hFile, (PLARGE_INTEGER)&cbView_))
    throw std::runtime_error("failed to get the file size");

  pView_ = ::MapViewOfFile(hMap_, FILE_MAP_READ, 0, 0, (size_t)cbView_);
  if (pView_ == NULL)
    throw std::runtime_error("failed to map the file");
}

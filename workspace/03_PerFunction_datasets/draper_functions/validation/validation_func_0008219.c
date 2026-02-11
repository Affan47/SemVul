changeFileTimestamp(const char *fileName,
                                          time_t timestamp)
{
  if (ArUtil::isStrEmpty(fileName)) {
    ArLog::log(ArLog::Normal,
               "Cannot change date on file with empty name");
    return false;
  }
#ifdef WIN32

  FILETIME fileTime;

  HANDLE hFile = CreateFile(fileName,
                            GENERIC_READ | GENERIC_WRITE,
                             0,NULL,
                             OPEN_EXISTING,
                             0,NULL);

  if (hFile == NULL) {
    return false;
  }


  LONGLONG temp = Int32x32To64(timestamp, 10000000) + 116444736000000000;
  fileTime.dwLowDateTime = (DWORD) temp;
  fileTime.dwHighDateTime = temp >> 32;

  SetFileTime(hFile,
              &fileTime,
              (LPFILETIME) NULL,
              &fileTime);

  CloseHandle(hFile);

#else

  char timeBuf[500];
  strftime(timeBuf, sizeof(timeBuf), "%c", ::localtime(&timestamp));
  ArLog::log(ArLog::Normal,
             "Changing file %s modified time to %s",
             fileName,
             timeBuf);


  struct utimbuf fileTime;
  fileTime.actime  = timestamp;
  fileTime.modtime = timestamp;
  utime(fileName, &fileTime);

#endif

  return true;

}

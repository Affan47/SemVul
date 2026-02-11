readDataPoint( char *line)
{
  if (line == NULL) {
    return false;
  }

  int x = 0;
  int y = 0;

  bool isSuccess  = true;
  size_t lineLen  = strlen(line) + 1;
  int startIndex  = 0;
  size_t parsedCount = 0;

  isSuccess = parseNumber(&line[startIndex], lineLen, &parsedCount, &x);

  startIndex += parsedCount;
  lineLen -= parsedCount;

  if (!isSuccess) {
    ArLog::log(ArLog::Normal,
               "%sArMapScan::readDataPoint error parsing x (startIndex = %i, lineLen = %i) in '%s'",
               myLogPrefix.c_str(), startIndex, lineLen, line);
    return false;
  }


  isSuccess = parseWhitespace(&line[startIndex], lineLen, &parsedCount);

  startIndex += parsedCount;
  lineLen -= parsedCount;

  if (!isSuccess) {
    ArLog::log(ArLog::Normal,
               "%sArMapScan::readDataPoint error parsing first whitespace (startIndex = %i, lineLen = %i) in '%s'",
               myLogPrefix.c_str(), startIndex, lineLen, line);
    return false;
  }


  isSuccess = parseNumber(&line[startIndex], lineLen, &parsedCount, &y);

  startIndex += parsedCount;
  lineLen -= parsedCount;

  if (!isSuccess) {
    ArLog::log(ArLog::Normal,
               "%sArMapScan::readDataPoint error parsing y (startIndex = %i, lineLen = %i) in '%s'",
               myLogPrefix.c_str(), startIndex, lineLen, line);
    return false;
  }


  loadDataPoint(x, y);

  return true;

}

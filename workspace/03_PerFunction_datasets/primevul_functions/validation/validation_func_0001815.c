bool CPlayListASX::LoadAsxIniInfo(std::istream &stream)
{
  CLog::Log(LOGINFO, "Parsing INI style ASX");

  std::string name, value;

  while( stream.good() )
  {

    while((stream.peek() == '\r' || stream.peek() == '\n' || stream.peek() == ' ') && stream.good())
      stream.get();

    if(stream.peek() == '[')
    {

      while(stream.good() && stream.peek() != '\r' && stream.peek() != '\n')
        stream.get();
      continue;
    }
    name = "";
    value = "";

    while(stream.peek() != '\r' && stream.peek() != '\n' && stream.peek() != '=' && stream.good())
      name += stream.get();


    if(stream.get() != '=')
      continue;


    while(stream.peek() != '\r' && stream.peek() != '\n' && stream.good())
      value += stream.get();

    CLog::Log(LOGINFO, "Adding element {}={}", name, value);
    CFileItemPtr newItem(new CFileItem(value));
    newItem->SetPath(value);
    if (newItem->IsVideo() && !newItem->HasVideoInfoTag())
      newItem->GetVideoInfoTag()->Reset();
    Add(newItem);
  }

  return true;
}

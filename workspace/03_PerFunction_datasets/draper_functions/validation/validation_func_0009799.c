findAndReplace(std::string & source, const std::string & find, const std::string & replace)
{

  size_t pos = 0;
  size_t findLength = find.length();
  size_t replaceLength = replace.length();

  do
  {

    pos = source.find(find, pos);


    if (pos != std::string::npos)
    {

      source.replace(pos, findLength, replace);


      pos = pos + replaceLength;
    }
  }
  while (pos != std::string::npos);
}

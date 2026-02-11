SplitString(std::vector<std::string>& args,
                                       std::string const& line)
{
  std::string::size_type pos1 = 0;
  std::string::size_type pos2 = line.find(',', 0);
  if(pos2 == std::string::npos)
    {
    return false;
    }
  std::string arg;
  while(pos2 != std::string::npos)
    {
    arg = line.substr(pos1, pos2-pos1);
    args.push_back(arg);
    pos1 = pos2+1;
    pos2 = line.find(',',pos1);
    }
  arg = line.substr(pos1);
  args.push_back(arg);
  return true;
}

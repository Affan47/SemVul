AddRPathCheckRule(std::ostream& os, Indent const& indent,
                    const char* config, std::string const& toDestDirPath)
{

  if(this->ImportLibrary || !this->Target->IsChrpathUsed(config))
    {
    return;
    }


  cmComputeLinkInformation* cli = this->Target->GetLinkInformation(config);
  if(!cli)
    {
    return;
    }


  std::string newRpath = cli->GetChrpathString();


  os << indent << "FILE(RPATH_CHECK\n"
     << indent << "     FILE \"" << toDestDirPath << "\"\n"
     << indent << "     RPATH \"" << newRpath << "\")\n";
}

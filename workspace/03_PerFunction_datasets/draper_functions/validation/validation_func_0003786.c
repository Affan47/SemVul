WriteRule(std::ostream& os,
                                       const std::string& name,
                                       const std::string& command,
                                       const std::string& description,
                                       const std::string& comment,
                                       const std::string& depfile,
                                       const std::string& rspfile,
                                       const std::string& rspcontent,
                                       bool restat,
                                       bool generator)
{

  if(name.empty())
    {
    cmSystemTools::Error("No name given for WriteRuleStatement! called "
                         "with comment: ",
                         comment.c_str());
    return;
    }


  if(command.empty())
    {
    cmSystemTools::Error("No command given for WriteRuleStatement! called "
                         "with comment: ",
                         comment.c_str());
    return;
    }

  cmGlobalNinjaGenerator::WriteComment(os, comment);


  os << "rule " << name << "\n";


  if(!depfile.empty())
    {
    cmGlobalNinjaGenerator::Indent(os, 1);
    os << "depfile = " << depfile << "\n";
    }


  cmGlobalNinjaGenerator::Indent(os, 1);
  os << "command = " << command << "\n";


  if(!description.empty())
    {
    cmGlobalNinjaGenerator::Indent(os, 1);
    os << "description = " << description << "\n";
    }

  if(!rspfile.empty())
    {
    if (rspcontent.empty())
      {
      cmSystemTools::Error("No rspfile_content given!", comment.c_str());
      return;
      }
    cmGlobalNinjaGenerator::Indent(os, 1);
    os << "rspfile = " << rspfile << "\n";
    cmGlobalNinjaGenerator::Indent(os, 1);
    os << "rspfile_content = " << rspcontent << "\n";
    }

  if(restat)
    {
    cmGlobalNinjaGenerator::Indent(os, 1);
    os << "restat = 1\n";
    }

  if(generator)
    {
    cmGlobalNinjaGenerator::Indent(os, 1);
    os << "generator = 1\n";
    }

  os << "\n";
}

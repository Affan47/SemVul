ReplaceString(std::string& source,
                                const std::string& replace,
                                const std::string& with)
{

  if (replace.empty()) {
    return;
  }

  SystemTools::ReplaceString(source, replace.c_str(), replace.size(), with);
}

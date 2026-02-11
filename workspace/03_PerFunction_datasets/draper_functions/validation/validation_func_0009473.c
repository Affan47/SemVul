AppendCleanCommand(std::vector<std::string>& commands,
                     const std::vector<std::string>& files,
                     cmTarget& target, const char* filename)
{
  if(!files.empty())
    {
    std::string cleanfile = this->Makefile->GetCurrentOutputDirectory();
    cleanfile += "/";
    cleanfile += this->GetTargetDirectory(target);
    cleanfile += "/cmake_clean";
    if(filename)
      {
      cleanfile += "_";
      cleanfile += filename;
      }
    cleanfile += ".cmake";
    std::string cleanfilePath = this->Convert(cleanfile.c_str(), FULL);
    std::ofstream fout(cleanfilePath.c_str());
    if(!fout)
      {
      cmSystemTools::Error("Could not create ", cleanfilePath.c_str());
      }
    fout << "FILE(REMOVE_RECURSE\n";
    std::string remove = "$(CMAKE_COMMAND) -P ";
    remove += this->Convert(cleanfile.c_str(), START_OUTPUT, SHELL);
    for(std::vector<std::string>::const_iterator f = files.begin();
        f != files.end(); ++f)
      {
      std::string fc = this->Convert(f->c_str(),START_OUTPUT,UNCHANGED);
      fout << "  " << this->EscapeForCMake(fc.c_str()) << "\n";
      }
    fout << ")\n";
    commands.push_back(remove);


    if(!filename)
      {

      std::set<cmStdString> languages;
      target.GetLanguages(languages);
      fout << "\n"
           << "# Per-language clean rules from dependency scanning.\n"
           << "FOREACH(lang";
      for(std::set<cmStdString>::const_iterator l = languages.begin();
          l != languages.end(); ++l)
        {
        fout << " " << *l;
        }
      fout << ")\n"
           << "  INCLUDE(" << this->GetTargetDirectory(target)
           << "/cmake_clean_${lang}.cmake OPTIONAL)\n"
           << "ENDFOREACH(lang)\n";
      }
    }
}

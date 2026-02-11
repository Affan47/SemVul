ReadInputFile()
{

  std::string currentStart = this->Makefile->GetStartDirectory();
  currentStart += "/CMakeLists.txt";
  if(cmSystemTools::FileExists(currentStart.c_str(), true))
    {
    this->Makefile->ReadListFile(currentStart.c_str());
    return;
    }

  if(!this->Parent)
    {
    return;
    }


  cmMakefile* mf = this->Parent->GetMakefile();
  cmOStringStream e;
  e << "The source directory\n"
    << "  " << this->Makefile->GetStartDirectory() << "\n"
    << "does not contain a CMakeLists.txt file.";
  switch (mf->GetPolicyStatus(cmPolicies::CMP0014))
    {
    case cmPolicies::WARN:

      e << "\n"
        << "CMake does not support this case but it used "
        << "to work accidentally and is being allowed for "
        << "compatibility."
        << "\n"
        << mf->GetPolicies()->GetPolicyWarning(cmPolicies::CMP0014);
      mf->IssueMessage(cmake::AUTHOR_WARNING, e.str());
    case cmPolicies::OLD:

      return;
    case cmPolicies::REQUIRED_IF_USED:
    case cmPolicies::REQUIRED_ALWAYS:
      e << "\n"
        << mf->GetPolicies()->GetRequiredPolicyError(cmPolicies::CMP0014);
    case cmPolicies::NEW:

      mf->IssueMessage(cmake::FATAL_ERROR, e.str());
      break;
    }
}

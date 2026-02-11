ApplyPolicyVersion(cmMakefile *mf,
                                    const char *version)
{
  std::string ver = "2.4.0";

  if (version && strlen(version) > 0)
  {
    ver = version;
  }

  unsigned int majorVer = 2;
  unsigned int minorVer = 0;
  unsigned int patchVer = 0;


  if(sscanf(ver.c_str(), "%u.%u.%u",
            &majorVer, &minorVer, &patchVer) < 2)
    {
    cmOStringStream e;
    e << "Invalid policy version value \"" << ver << "\".  "
      << "A numeric major.minor[.patch] must be given.";
    mf->IssueMessage(cmake::FATAL_ERROR, e.str());
    return false;
    }


  if (majorVer < 2 || majorVer == 2 && minorVer < 4)
    {
    mf->IssueMessage(cmake::FATAL_ERROR,
      "An attempt was made to set the policy version of CMake to something "
      "earlier than \"2.4\".  "
      "In CMake 2.4 and below backwards compatibility was handled with the "
      "CMAKE_BACKWARDS_COMPATIBILITY variable.  "
      "In order to get compatibility features supporting versions earlier "
      "than 2.4 set policy CMP0001 to OLD to tell CMake to check the "
      "CMAKE_BACKWARDS_COMPATIBILITY variable.  "
      "One way to do this is to set the policy version to 2.4 exactly."
      );
    return false;
    }


  if (majorVer > cmVersion::GetMajorVersion() ||
      (majorVer == cmVersion::GetMajorVersion() &&
       minorVer > cmVersion::GetMinorVersion()) ||
      (majorVer == cmVersion::GetMajorVersion() &&
       minorVer == cmVersion::GetMinorVersion() &&
       patchVer > cmVersion::GetPatchVersion()))
    {
    cmOStringStream e;
    e << "An attempt was made to set the policy version of CMake to \""
      << version << "\" which is greater than this version of CMake.  "
      << "This is not allowed because the greater version may have new "
      << "policies not known to this CMake.  "
      << "You may need a newer CMake version to build this project.";
    mf->IssueMessage(cmake::FATAL_ERROR, e.str());
    return false;
    }


  std::vector<cmPolicies::PolicyID> ancientPolicies;
  std::map<cmPolicies::PolicyID,cmPolicy *>::iterator i
    = this->Policies.begin();
  for (;i != this->Policies.end(); ++i)
  {
    if (i->second->IsPolicyNewerThan(majorVer,minorVer,patchVer))
    {
      if(i->second->Status == cmPolicies::REQUIRED_ALWAYS)
      {
        ancientPolicies.push_back(i->first);
      }
      else if (!mf->SetPolicy(i->second->ID, cmPolicies::WARN))
      {
        return false;
      }
    }
    else
    {
      if (!mf->SetPolicy(i->second->ID, cmPolicies::NEW))
      {
        return false;
      }
    }
  }


  if(!ancientPolicies.empty())
    {
    this->DiagnoseAncientPolicies(ancientPolicies,
                                  majorVer, minorVer, patchVer, mf);
    cmSystemTools::SetFatalErrorOccured();
    return false;
    }

  return true;
}

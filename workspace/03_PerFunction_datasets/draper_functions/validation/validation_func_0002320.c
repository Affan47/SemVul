FinalizeTargetCompileDefinitions()
{

  for(unsigned int i=0; i < this->LocalGenerators.size(); ++i)
    {
    cmMakefile *mf = this->LocalGenerators[i]->GetMakefile();

    const std::vector<cmValueWithOrigin> noconfig_compile_definitions =
                                mf->GetCompileDefinitionsEntries();

    std::vector<std::string> configs;
    mf->GetConfigurations(configs);

    cmTargets& targets = mf->GetTargets();
    for(cmTargets::iterator ti = targets.begin();
        ti != targets.end(); ++ti)
      {
      cmTarget* t = &ti->second;

      for (std::vector<cmValueWithOrigin>::const_iterator it
                                      = noconfig_compile_definitions.begin();
          it != noconfig_compile_definitions.end(); ++it)
        {
        t->InsertCompileDefinition(*it);
        }

      for(std::vector<std::string>::const_iterator ci = configs.begin();
          ci != configs.end(); ++ci)
        {
        std::string defPropName = "COMPILE_DEFINITIONS_";
        defPropName += cmSystemTools::UpperCase(*ci);
        t->AppendProperty(defPropName.c_str(),
                          mf->GetProperty(defPropName.c_str()));
        }
      }
    }
}

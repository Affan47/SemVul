findSection(const char *sectionName) const
{
  ArConfigSection *section = NULL;
  ArConfigSection *tempSection = NULL;

  for (std::list<ArConfigSection *>::const_iterator sectionIt = mySections.begin();
       sectionIt != mySections.end();
       sectionIt++)
  {
    tempSection = (*sectionIt);
    if (ArUtil::strcasecmp(tempSection->getName(), sectionName) == 0)
    {
      section = tempSection;
    }
  }
  return section;

}

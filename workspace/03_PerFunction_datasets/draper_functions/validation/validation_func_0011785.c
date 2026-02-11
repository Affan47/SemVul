parseElementNameGroup(unsigned declInputLevel, Param &parm)
{
  if (!parseNameGroup(declInputLevel, parm))
    return 0;
  parm.elementVector.resize(parm.nameTokenVector.size());
  for (size_t i = 0; i < parm.nameTokenVector.size(); i++)
    parm.elementVector[i] = lookupCreateElement(parm.nameTokenVector[i].name);
  return 1;
}

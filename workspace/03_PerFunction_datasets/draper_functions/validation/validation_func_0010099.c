GetRegisteredGenerators(std::vector<std::string>& names)
{
  for(RegisteredGeneratorsVector::const_iterator i = this->Generators.begin();
      i != this->Generators.end(); ++i)
    {
    (*i)->GetGenerators(names);
    }
  for(RegisteredExtraGeneratorsMap::const_iterator
      i = this->ExtraGenerators.begin();
      i != this->ExtraGenerators.end(); ++i)
    {
    names.push_back(i->first);
    }
}

get_sections() const
{
  std::vector<XMLReader> lst;
  if (root)
    {
      for(std::vector<XMLNode*>::const_iterator i = root->children.begin(); i != root->children.end(); ++i)
        {
          lst.push_back(XMLReader(dynamic_cast<XMLListNode*>(*i)));
        }
    }
  return lst;
}

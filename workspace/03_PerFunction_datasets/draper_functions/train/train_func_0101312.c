ParseRootNodeNamesFile( IBFabric *p_fabric, string fileName)
{
  ifstream namesFile;
  namesFile.open(fileName.c_str(), ifstream::in);
  if (!namesFile.is_open())
  {
    cout << "-F- Given roots file could not be opened!" << endl;
    exit(1);
  }

  char name[256];
  list <IBNode *> roots;
  cout << "-I- Parsing Root Node Names from file:" << fileName << endl;
  namesFile.getline(name,256);
  while (namesFile.good())
  {
    IBNode *pNode = p_fabric->getNode(string(name));
    if (!pNode)
    {
      cout << "-E- Fail to find node:" << name << endl;
    }
    else
    {
      roots.push_back(pNode);
    }
    namesFile.getline(name,256);
  }
  cout << "-I- Defined " << roots.size() << " root nodes" << endl;
  namesFile.close();
  return roots;
}

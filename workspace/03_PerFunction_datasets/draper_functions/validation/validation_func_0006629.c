Load(const std::string &filePathSource,
																			 const std::string &filePathTarget)
{

  ifstream inFileSource(filePathSource.c_str());
  if (!inFileSource)
  {
      cerr << "could not open file " << filePathSource << endl;
      return false;
  }

  std::string line;
  while (getline(inFileSource, line)) {
    m_vocabSource.insert(line);
  }

  inFileSource.close();


  ifstream inFileTarget(filePathTarget.c_str());
  if (!inFileTarget)
  {
      cerr << "could not open file " << filePathTarget << endl;
      return false;
  }

  while (getline(inFileTarget, line)) {
    m_vocabTarget.insert(line);
  }

  inFileTarget.close();

  m_unrestricted = false;
  return true;
}

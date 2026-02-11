CanReadFile(const char *filename)
{

  GenericCUBFileAdaptor *reader = CreateReader(filename);

  if ( reader == ITK_NULLPTR )
    {
    itkDebugMacro(<< "The file is not a valid CUB file");
    return false;
    }


  bool iscub = true;
  try
    {

    std::istringstream iss( reader->ReadHeader() );


    std::string word;


    iss >> word;
    if ( word != m_VB_IDENTIFIER_SYSTEM )
      {
      iscub = false;
      }


    iss >> word;
    if ( word != m_VB_IDENTIFIER_FILETYPE )
      {
      iscub = false;
      }
    }
  catch ( ... )
    {
    iscub = false;
    }

  delete reader;
  return iscub;
}

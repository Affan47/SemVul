GetFormFromFilename(
                                                   const std::string& filename,
                                                   int* manSection)
{
  std::string ext = cmSystemTools::GetFilenameLastExtension(filename);
  ext = cmSystemTools::UpperCase(ext);
  if ((ext == ".HTM") || (ext == ".HTML"))
    {
    return cmDocumentation::HTMLForm;
    }

  if (ext == ".DOCBOOK")
    {
    return cmDocumentation::DocbookForm;
    }


  if ((ext.length()==2) && (ext[1] >='1') && (ext[1]<='9'))
    {
    if (manSection)
      {
      *manSection = ext[1] - '0';
      }
    return cmDocumentation::ManForm;
    }

  return cmDocumentation::TextForm;
}

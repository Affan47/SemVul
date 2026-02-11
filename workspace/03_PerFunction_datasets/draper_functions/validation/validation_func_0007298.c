iGIFReadApplication(imBinFile* handle, imAttribTable* attrib_table)
{
  char identifier[9];


  imBinFileSeekOffset(handle, 1);


  imBinFileRead(handle, identifier, 8, 1);
  if (identifier[7] != 0)
    identifier[8] = 0;

  if (imBinFileError(handle))
    return IM_ERR_ACCESS;

  if (imStrEqual(identifier, "NETSCAPE"))
  {
    unsigned char authentication[4];

    imBinFileRead(handle, authentication, 3, 1);
    authentication[3] = 0;

    if (imBinFileError(handle))
      return IM_ERR_ACCESS;

    if (strcmp((char*)authentication, "2.0") == 0)
    {
      unsigned short word_value;


      imBinFileSeekOffset(handle, 2);


      imBinFileRead(handle, &word_value, 1, 2);

      attrib_table->Set("Iterations", IM_USHORT, 1, &word_value);


      imBinFileSeekOffset(handle, 1);

      if (imBinFileError(handle))
        return IM_ERR_ACCESS;
    }
    else
    {

      if (iGIFSkipSubBlocks(handle) != IM_ERR_NONE)
        return IM_ERR_ACCESS;
    }
  }
  else
  {

    imBinFileSeekOffset(handle, 3);


    if (iGIFSkipSubBlocks(handle) != IM_ERR_NONE)
      return IM_ERR_ACCESS;
  }

  return IM_ERR_NONE;
}

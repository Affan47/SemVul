static void renameOnEndOfStudy()


{
  int counter = 1;

  OFListIterator(OFString) first = outputFileNameArray.begin();
  OFListIterator(OFString) last = outputFileNameArray.end();


  if( !endOfStudyThroughTimeoutEvent ) --last;


  while (first != last)
  {


    char modalityId[3];
    char newFileName[9];
    if (opt_timeNames)
    {

      size_t serialPos = (*first).find("_");
      if (serialPos != OFString_npos)
      {

        OFStandard::strlcpy( modalityId, (*first).substr(serialPos+6, 2).c_str(), 3 );
      }
      else
      {

        OFStandard::strlcpy( modalityId, (*first).substr(18, 2).c_str(), 3 );
      }
    }
    else
    {
      OFStandard::strlcpy( modalityId, (*first).c_str(), 3 );
    }
    sprintf( newFileName, "%s%06d", modalityId, counter );


    OFString oldPathAndFileName;
    oldPathAndFileName = lastStudySubdirectoryPathAndName;
    oldPathAndFileName += PATH_SEPARATOR;
    oldPathAndFileName += *first;

    OFString newPathAndFileName;
    newPathAndFileName = lastStudySubdirectoryPathAndName;
    newPathAndFileName += PATH_SEPARATOR;
    newPathAndFileName += newFileName;


    if( rename( oldPathAndFileName.c_str(), newPathAndFileName.c_str() ) != 0 )
      OFLOG_WARN(storescpLogger, "cannot rename file '" << oldPathAndFileName << "' to '" << newPathAndFileName << "'");


    first = outputFileNameArray.erase(first);


    counter++;
  }
}

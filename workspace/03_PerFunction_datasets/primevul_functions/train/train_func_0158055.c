static void executeOnReception()


{
  OFString cmd = opt_execOnReception;


  if( !opt_ignore )
  {

    OFString dir = (opt_sortStudyMode == ESM_None) ? opt_outputDirectory : subdirectoryPathAndName;
    cmd = replaceChars( cmd, OFString(PATH_PLACEHOLDER), dir );


    OFString outputFileName = outputFileNameArray.back();
    cmd = replaceChars( cmd, OFString(FILENAME_PLACEHOLDER), outputFileName );
  }


  cmd = replaceChars( cmd, OFString(CALLING_AETITLE_PLACEHOLDER), callingAETitle );


  cmd = replaceChars( cmd, OFString(CALLED_AETITLE_PLACEHOLDER), calledAETitle );


  cmd = replaceChars( cmd, OFString(CALLING_PRESENTATION_ADDRESS_PLACEHOLDER), callingPresentationAddress );


  executeCommand( cmd );
}

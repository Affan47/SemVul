addError( ErrorXML & error,
                     bool       lastError ) throw( MissingException )
{
   bool firstpara = true;
   string tmp;
   string & errNumber = error.GetErrNumber();
   string & errName   = error.GetErrName();
   const char * paragraph;
   string errMessage;
   const char * msg;

   if ( my_javadocStyle ) {


      outStream << "    /**" << endl;

      paragraph = error.GetDocuParagraph();
      while ( paragraph != NULL ) {
         stripText( paragraph, tmp );
         if ( tmp.empty() ) throw new MissingException( "<errordoc>" );

         if ( firstpara ) firstpara = false;
         else {
            outStream << "     * <p>" << endl;
         }

         formatText( outStream, tmp, "     * ", ERRP_LINE_LENGTH );

         paragraph = error.GetDocuParagraph();
      }
      outStream << "     */" << endl;
   }
   else {
      paragraph = error.GetDocuParagraph();
      while ( paragraph != NULL ) {
         stripText( paragraph, tmp );
         if ( tmp.empty() ) throw new MissingException( "<errordoc>" );

         if ( firstpara ) firstpara = false;
         else {
            outStream << "    //" << endl;
         }
         formatText( outStream, tmp, "    // ", ERRP_LINE_LENGTH );

         paragraph = error.GetDocuParagraph();
      }
   }

   msg = error.GetErrMessage();
   g_msgXML->GetErrMessage( msg, errMessage );

   outStream << "    " << errName << "(" << errNumber << ") {" << endl;
   outStream << "        String getMessage() { return \"" << errMessage << "\"; } }";

   if (lastError) outStream << ";" << endl << endl;
   else outStream << "," << endl << endl;
}

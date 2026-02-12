void PDFDoc::writeXRefStreamTrailer (Object &&trailerDict, XRef *uxref, Ref *uxrefStreamRef, Goffset uxrefOffset, OutStream* outStr, XRef *xRef)
{
  GooString stmData;


  uxref->writeStreamToBuffer(&stmData, trailerDict.getDict(), xRef);


  MemStream *mStream = new MemStream( stmData.c_str(), 0, stmData.getLength(), std::move(trailerDict) );
  writeObjectHeader(uxrefStreamRef, outStr);
  Object obj1(static_cast<Stream*>(mStream));
  writeObject(&obj1, outStr, xRef, 0, nullptr, cryptRC4, 0, 0, 0);
  writeObjectFooter(outStr);

  outStr->printf( "startxref\r\n");
  outStr->printf( "%lli\r\n", uxrefOffset);
  outStr->printf( "%%%%EOF\r\n");
}

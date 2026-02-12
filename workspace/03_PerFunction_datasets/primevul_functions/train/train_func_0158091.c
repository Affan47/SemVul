static OFString AddStatusDetail( DcmDataset **statusDetail, const DcmElement *elem )


{

  if( elem == NULL )
    return "";

  OFOStringStream log;
  DcmAttributeTag *at;
  DcmLongString *lo;


  if( *statusDetail == NULL )
    *statusDetail = new DcmDataset();


  DcmVR vr( elem->ident() );


  log << "Status Detail:" << OFendl;


  switch( elem->ident() )
  {
    case EVR_LO:
      lo = new DcmLongString( *((DcmLongString*)elem) );
      if( lo->getLength() > vr.getMaxValueLength() )
      {
        log << "AddStatusDetail: INTERNAL ERROR: value too large (max " << (unsigned long)(vr.getMaxValueLength())
            << ") for " << vr.getVRName() << ": " << OFendl;
      }
      (*statusDetail)->insert( lo, OFTrue  );
      lo->print(log);
      break;
    case EVR_AT:
      at = new DcmAttributeTag( *((DcmAttributeTag*)elem) );
      if( at->getLength() > vr.getMaxValueLength() )
      {
        log << "AddStatusDetail: INTERNAL ERROR: value too large (max " << (unsigned long)(vr.getMaxValueLength())
            << ") for " << vr.getVRName() << ": " << OFendl;
      }
      (*statusDetail)->insert( at, OFTrue  );
      at->print(log);
      break;
    default:

      log << "AddStatusDetail: unsupported status detail type: " << vr.getVRName() << OFendl;
      break;
  }
  log << OFStringStream_ends;
  OFSTRINGSTREAM_GETOFSTRING(log, ret)
  return ret;
}

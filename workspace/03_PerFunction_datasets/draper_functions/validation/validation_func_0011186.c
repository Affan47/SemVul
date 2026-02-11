xmlstring() const{

    xmlNode *n = xml( true, false );
    xmlSetNs( n, xmlNewNs( n, (const xmlChar *)NSFOLIA.c_str(), 0 ) );
    xmlBuffer *buf = xmlBufferCreate();
    xmlNodeDump( buf, 0, n, 0, 0 );
    string result = (const char*)xmlBufferContent( buf );
    xmlBufferFree( buf );
    xmlFreeNode( n );
    return result;
  }

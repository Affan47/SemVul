quoteFilename(const char *zFilename){
  int i, c;
  int needQuote = 0;
  for(i=0; (c = zFilename[i])!=0; i++){
    if( c=='"' ) return 0;
    if( fossil_isspace(c) ) needQuote = 1;
    if( c=='\\' && zFilename[i+1]==0 ) return 0;
    if( c=='$' ) return 0;
  }
  if( needQuote ){
    return mprintf("\"%s\"", zFilename);
  }else{
    return mprintf("%s", zFilename);
  }
}

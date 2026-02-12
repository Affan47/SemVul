void sqlite3Fts3Dequote(char *z){
  char quote;

  quote = z[0];
  if( quote=='[' || quote=='\'' || quote=='"' || quote=='`' ){
    int iIn = 1;
    int iOut = 0;


    if( quote=='[' ) quote = ']';

    while( ALWAYS(z[iIn]) ){
      if( z[iIn]==quote ){
        if( z[iIn+1]!=quote ) break;
        z[iOut++] = quote;
        iIn += 2;
      }else{
        z[iOut++] = z[iIn++];
      }
    }
    z[iOut] = '\0';
  }
}

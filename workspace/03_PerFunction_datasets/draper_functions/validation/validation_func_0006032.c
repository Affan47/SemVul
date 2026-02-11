errMsg(int err_level, char* str1, char* str2, char* str3, char* str4)
{
  strstream strm;

  if ( str1 != NULL ) strm << str1;
  if ( str2 != NULL ) strm << str2;
  if ( str3 != NULL ) strm << str3;
  if ( str4 != NULL ) strm << str4;
  strm << ends;

  if ( strm.str() != NULL ) cerr << strm.str();

}

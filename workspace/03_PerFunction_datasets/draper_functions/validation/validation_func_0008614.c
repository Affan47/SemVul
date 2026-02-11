make_number( const char* s )
{
  int numerator_ = 0;
  int denominator_ = 1;
  const char* si = s;
  for( ; *si != '\0' && *si != '.' && *si != '/'; ++si )
    numerator_ = 10 * numerator_ + (*si - '0');

  if( *si == '/' )
    {
      denominator_ = 0;
      for( ++si; *si != '\0'; ++si )
	denominator_ = 10*denominator_ + (*si - '0');
      if( denominator_ == 0 )
      {
        std::cout<<"ERROR: division by 0"<<std::endl;
	exit(1);
      }
      yylval.num = new double(((double)numerator_) / ((double)denominator_));
    }
  else if( *si == '.' )
    {
      int a = numerator_;
      double fr = 0;
      int j = 1;
      for( ++si; *si != '\0'; ++si, j++ )
	{
	  fr += ((*si - '0') / (pow(10, j)));
	}
      yylval.num = new double(a + fr);
    }
  else
    {
      yylval.num = new double(numerator_);
    }
  return( NUMBER );
}

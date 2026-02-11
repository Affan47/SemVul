MatchWith( const std::string& s1, const std::string& s2, bool ignoreCase )
{

  if ( ignoreCase )
    {

    std::string ls1 = s1;
    ToLowerCase( ls1 );

    std::string ls2 = s2;
    ToLowerCase( ls2 );

    if ( ls1 == ls2 )
      {
      return true;
      }
    else
      {
      return false;
      }
    }


  if ( s1 == s2 )
    {
    return true;
    }
  else
    {
    return false;
    }
}

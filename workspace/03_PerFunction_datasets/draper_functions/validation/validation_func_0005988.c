operator- ( const jalib::JTime& a, const jalib::JTime& b )
{
  double sec = a._value.tv_sec - b._value.tv_sec;
  sec += ( a._value.tv_usec-b._value.tv_usec ) /1000000.0;
  if ( sec < 0 ) sec *= -1;
  return sec;
}

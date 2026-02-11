numCols( void ) const
{
  int t = a_type();
  int r = rank();

  if (t==Ct || r==0)            return 1;
  else if (r==2)                return d1();
  else if (t==Et &&
	   isNull(a())==MSTrue) return 0;
  else if (t==Et)               return 1;
  else if (r==1)                return 1;
  else                          return d1();
}

dJulian ()
{
  int DaysInYear = 365;
  if (leapYear ()) DaysInYear++;
  return ( year + 1.0 * (dayofyear (year, month, day) - 1) / DaysInYear);
}

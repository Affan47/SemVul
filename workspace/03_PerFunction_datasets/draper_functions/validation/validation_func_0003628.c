daysinmonth (int month, int leap)
{

  if (month < JANUARY || month > DECEMBER)
    return -1;


  switch (month) {
    case FEBRUARY:
      return leap ? 29 : 28;
    default:
      return mdays[month];
  }
}

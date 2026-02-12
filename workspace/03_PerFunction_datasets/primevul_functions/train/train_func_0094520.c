int MAPISysTimetoDTR(BYTE *data, dtr *thedate) {
  DDWORD ddword_tmp;
  int startingdate = 0;
  int tmp_date;
  int days_in_year = 365;
  unsigned int months[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  ddword_tmp = *((DDWORD *)data);
  ddword_tmp = ddword_tmp / 10;
  ddword_tmp /= 1000;
  ddword_tmp /= 1000;

  thedate->wSecond = (ddword_tmp % 60);

  ddword_tmp /= 60;
  thedate->wMinute = (ddword_tmp % 60);

  ddword_tmp /= 60;
  thedate->wHour = (ddword_tmp % 24);

  ddword_tmp /= 24;


  thedate->wYear = 1601;
  startingdate = 1;
  while (ddword_tmp >= days_in_year) {
    ddword_tmp -= days_in_year;
    thedate->wYear++;
    days_in_year = 365;
    startingdate++;
    if ((thedate->wYear % 4) == 0) {
      if ((thedate->wYear % 100) == 0) {


        if ((thedate->wYear % 400) == 0) {
          startingdate++;
          days_in_year = 366;
        }
      }  else {
        startingdate++;
        days_in_year = 366;
      }
    }
    startingdate %= 7;
  }


  if ((thedate->wYear % 4) == 0) {

    months[1] = 29;
  }

  tmp_date = (int)ddword_tmp;
  thedate->wDayOfWeek = (tmp_date + startingdate) % 7;
  thedate->wMonth = 0;

  while (tmp_date > months[thedate->wMonth]) {
    tmp_date -= months[thedate->wMonth];
    thedate->wMonth++;
  }
  thedate->wMonth++;
  thedate->wDay = tmp_date + 1;
  return 0;
}

cbf_gregorian_julian (int    year,
                             int    month,
                             int    day,
                             int    hour,
                             int    minute,
                             double second)
{
  static int days [] = {   0,  31,  59,  90, 120, 151,
                     181, 212, 243, 273, 304, 334, 365 };

  second += minute * 60.0 + hour * 3600.0 + (day - 1) * 86400.0;

  second += days [month - 1] * 86400.0;

  if (month > 2 && (year % 4) == 0 && year != 1900 && year != 2100)

    second += 86400.0;

  second += ((365 * (year - 1)) + floor ((year - 1) / 4)
                                - floor ((year - 1) / 100)
                                + floor ((year - 1) / 400)) * 86400.0;

  return second / 86400.0 + 1721425.5;
}

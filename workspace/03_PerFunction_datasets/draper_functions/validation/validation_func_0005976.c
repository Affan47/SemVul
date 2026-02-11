DateCalc_Day_of_Year(Z_int year, Z_int month, Z_int day)
{
    boolean leap;

    if ((year >= 1) and
        (month >= 1) and (month <= 12) and
        (day >= 1) and
        (day <= DateCalc_Days_in_Month_[leap=DateCalc_leap_year(year)][month]))
            return( DateCalc_Days_in_Year_[leap][month] + day );
    return(0);
}

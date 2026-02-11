monthNumberToMonthIndex(int year, int month) const
{
    if (isLeapYear(year)) {
        if (month == 6) {
            return 13;
        } else if (month == 7) {
            return 14;
        } else if (month > 7) {
            return month - 1;
        }
    }

    return month;
}

compareToRule(int8_t month, int8_t monthLen, int8_t prevMonthLen,
                              int8_t dayOfMonth,
                              int8_t dayOfWeek, int32_t millis, int32_t millisDelta,
                              EMode ruleMode, int8_t ruleMonth, int8_t ruleDayOfWeek,
                              int8_t ruleDay, int32_t ruleMillis)
{

    millis += millisDelta;
    while (millis >= U_MILLIS_PER_DAY) {
        millis -= U_MILLIS_PER_DAY;
        ++dayOfMonth;
        dayOfWeek = (int8_t)(1 + (dayOfWeek % 7));
        if (dayOfMonth > monthLen) {
            dayOfMonth = 1;


            ++month;
        }
    }
    while (millis < 0) {
        millis += U_MILLIS_PER_DAY;
        --dayOfMonth;
        dayOfWeek = (int8_t)(1 + ((dayOfWeek+5) % 7));
        if (dayOfMonth < 1) {
            dayOfMonth = prevMonthLen;
            --month;
        }
    }


    if (month < ruleMonth) return -1;
    else if (month > ruleMonth) return 1;


    int32_t ruleDayOfMonth = 0;


    if (ruleDay > monthLen) {
        ruleDay = monthLen;
    }

    switch (ruleMode)
    {

    case DOM_MODE:
        ruleDayOfMonth = ruleDay;
        break;


    case DOW_IN_MONTH_MODE:


        if (ruleDay > 0)
            ruleDayOfMonth = 1 + (ruleDay - 1) * 7 +
                (7 + ruleDayOfWeek - (dayOfWeek - dayOfMonth + 1)) % 7;


        else
        {


            ruleDayOfMonth = monthLen + (ruleDay + 1) * 7 -
                (7 + (dayOfWeek + monthLen - dayOfMonth) - ruleDayOfWeek) % 7;
        }
        break;

    case DOW_GE_DOM_MODE:
        ruleDayOfMonth = ruleDay +
            (49 + ruleDayOfWeek - ruleDay - dayOfWeek + dayOfMonth) % 7;
        break;

    case DOW_LE_DOM_MODE:
        ruleDayOfMonth = ruleDay -
            (49 - ruleDayOfWeek + ruleDay + dayOfWeek - dayOfMonth) % 7;


        break;
    }


    if (dayOfMonth < ruleDayOfMonth) return -1;
    else if (dayOfMonth > ruleDayOfMonth) return 1;


    if (millis < ruleMillis) return -1;
    else if (millis > ruleMillis) return 1;
    else return 0;
}

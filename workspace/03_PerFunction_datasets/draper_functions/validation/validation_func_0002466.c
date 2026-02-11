init_user_holidays( int hyear )
{
    holstorep_t tmpholp;

    char *s, *monthStr, *eventStr, nextChar;
    int index, inMonth, inDay, lineNum = 1;

    initStr (&s, MAX_LINE_LEN);
    initStr (&monthStr, MAX_LINE_LEN);
    rewind (inFile);
    nextChar = (char) getc (inFile);
    for (; !feof (inFile);
         lineNum++, nextChar = (char) getc (inFile))
    {
        ungetc (nextChar, inFile);
        if (!fgets (s, MAX_LINE_LEN, inFile))
        {
            warn ("input file read error. Skipping line %s", hc_itoa (lineNum));
            continue;
        }
        if (s[0] == '\n')
            continue;
        if (!sscanf (s, "%s %d%n", monthStr, &inDay, &index))
        {
            warn ("Error in input file.  Skipping line %s", hc_itoa (lineNum));
            continue;
        }
        if (isAllNums (monthStr))
        {
            warn ("Numeric hebrew month in input file.  Skipping line %s",
                  hc_itoa (lineNum));
            continue;
        }
        if (!(inMonth = lookup_hebrew_month (monthStr)))
        {
            warn ("Unrecognized hebrew month in input file.  Skipping line %s",
                  hc_itoa (lineNum));
            continue;
        }
        if (inDay < 1 || inDay > 30)
        {
            warn ("Date out of range in input file. Skipping line %s",
                  hc_itoa (lineNum));
            continue;
        }

        if (inMonth == ADAR_II && !LEAP_YR_HEB (hyear))
            inMonth = ADAR_I;

        eventStr = s + index + 1;
        if (eventStr[strlen (eventStr) - 1] == '\n')
            eventStr[strlen (eventStr) - 1] = '\0';


        tmpholp = getHolstorep ();
        initStr (&tmpholp->name, MAX_LINE_LEN);
        strcpy (tmpholp->name, eventStr);
        tmpholp->typeMask = USER_EVENT;
        PushHoliday (tmpholp, &var_holidays[inMonth][inDay]);

    }
}

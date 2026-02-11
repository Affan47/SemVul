store_time(void) {
    char **line;
    char *sql;
    int nrow, ncolumn;
    char date[50];
    time_t now;
    timeofday_t tod;

    cf_get_time(&tod);
    now = time(NULL);

    if (tod.day == last_stored_day)
        return 0;
    last_stored_day = tod.day;

    snprintf(date, 50, "%10d-%2d-%2d %2d:%2d", tod.year, tod.month, tod.day, tod.hour, tod.minute);

    sql = sqlite3_mprintf("select * from time where time_ingame='%q'", date);
    sqlite3_get_table(database, sql, &line, &nrow, &ncolumn, NULL);
    sqlite3_free(sql);
    sqlite3_free_table(line);
    if (nrow > 0)
        return 0;

    sql = sqlite3_mprintf("insert into time (time_ingame, time_real) values( '%s', %d )", date, now);
    do_sql(sql);
    sqlite3_free(sql);
    return 1;
}

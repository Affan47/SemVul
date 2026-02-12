Item_date_literal(THD *thd, MYSQL_TIME *ltime)
    :Item_temporal_literal(thd, ltime)
  {
    max_length= MAX_DATE_WIDTH;
    fixed= 1;


    maybe_null= !ltime->month || !ltime->day;
  }

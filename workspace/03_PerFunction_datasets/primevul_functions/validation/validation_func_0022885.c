Item_datetime_literal(THD *thd, MYSQL_TIME *ltime, uint dec_arg):
    Item_temporal_literal(thd, ltime, dec_arg)
  {
    max_length= MAX_DATETIME_WIDTH + (decimals ? decimals + 1 : 0);
    fixed= 1;

    maybe_null= !ltime->month || !ltime->day;
  }

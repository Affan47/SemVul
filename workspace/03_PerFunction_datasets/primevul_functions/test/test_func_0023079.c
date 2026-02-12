Item_date_literal(THD *thd, const Date *ltime)
    :Item_temporal_literal(thd),
     cached_time(*ltime)
  {
    DBUG_ASSERT(cached_time.is_valid_date());
    max_length= MAX_DATE_WIDTH;


    maybe_null= cached_time.check_date(TIME_NO_ZERO_DATE | TIME_NO_ZERO_IN_DATE);
  }

prev_insert_id(ulonglong nr, struct system_variables *variables)
{
  if (unlikely(nr < variables->auto_increment_offset))
  {


    DBUG_PRINT("info",("auto_increment: nr: %lu cannot honour "
                       "auto_increment_offset: %lu",
                       (ulong) nr, variables->auto_increment_offset));
    return nr;
  }
  if (variables->auto_increment_increment == 1)
    return nr;


  nr= (nr - variables->auto_increment_offset) /
      (ulonglong) variables->auto_increment_increment;


  return (nr * (ulonglong) variables->auto_increment_increment +
          variables->auto_increment_offset);
}

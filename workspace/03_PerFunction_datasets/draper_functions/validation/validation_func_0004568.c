log_everyone_out(time_t the_time, int update_time_flag,
                      int change_login_flag, char *debug_str)
{
  struct hashtab_order ho;
  struct hashtab_elem *he;

  for (he = hashtab_first (login_table, &ho);
       he != NULL;
       he = hashtab_next (&ho))
    {
      struct login_data *l = hashtab_get_value (he);

      if (update_time_flag)
        update_user_time (l->ut_name, the_time - l->time, debug_str);

      if (change_login_flag)
        l->time = the_time;
      else
        hashtab_delete (he);
    }
}

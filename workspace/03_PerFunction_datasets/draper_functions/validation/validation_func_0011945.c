update_global_user_stats(THD* thd, bool create_user, time_t now)
{
  char* user_string=         get_valid_user_string(thd->main_security_ctx.user);
  const char* client_string= get_client_host(thd);

  USER_STATS* user_stats;
  THREAD_STATS* thread_stats;
  mysql_mutex_lock(&LOCK_global_user_client_stats);


  if ((user_stats = (USER_STATS *) my_hash_search(&global_user_stats,
                                                  (uchar *) user_string,
                                                  strlen(user_string))))
  {

    update_global_user_stats_with_user(thd, user_stats, now);
  }
  else
  {

    if (create_user)
    {
      increment_count_by_name(user_string, user_string,
                              &global_user_stats, thd);
    }
  }


  if ((user_stats = (USER_STATS *) my_hash_search(&global_client_stats,
                                                  (uchar *) client_string,
                                                  strlen(client_string))))
  {

    update_global_user_stats_with_user(thd, user_stats, now);
  }
  else
  {

    if (create_user)
    {
      increment_count_by_name(client_string,
                              user_string,
                              &global_client_stats, thd);
    }
  }

  if (opt_thread_statistics)
  {

    if ((thread_stats = (THREAD_STATS *) my_hash_search(&global_thread_stats,
                                                        (uchar *) &(thd->thread_id),
                                                        sizeof(my_thread_id))))
    {

      update_global_thread_stats_with_thread(thd, thread_stats, now);
    }
    else
    {

      if (create_user)
      {
        increment_count_by_id(thd->thread_id,
                              &global_thread_stats, thd);
      }
    }
  }

  thd->last_global_update_time = now;
  thd->reset_diff_stats();

  mysql_mutex_unlock(&LOCK_global_user_client_stats);
}

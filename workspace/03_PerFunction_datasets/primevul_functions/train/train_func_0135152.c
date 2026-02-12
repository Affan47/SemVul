dirvote_recalculate_timing(const or_options_t *options, time_t now)
{
  voting_schedule_t *new_voting_schedule;

  if (!authdir_mode_v3(options)) {
    return;
  }


  new_voting_schedule = get_voting_schedule(options, now, LOG_NOTICE);
  tor_assert(new_voting_schedule);


  memcpy(&voting_schedule, new_voting_schedule, sizeof(voting_schedule));
  voting_schedule_free(new_voting_schedule);
}

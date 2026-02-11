entry_guards_changed(void)
{
  time_t when;
  entry_guards_dirty = 1;


  when = get_options()->AvoidDiskWrites ? time(NULL) + 3600 : time(NULL)+600;
  or_state_mark_dirty(get_or_state(), when);
}

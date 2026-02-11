switch_to_callback ( widget, data )
GtkWidget *widget;
gpointer data;
{
  TaskData *td;
  time_t now, diff;
  int loop;
  int new_icon = 1;
  int st = get_selected_task ();

  for ( loop = 0; loop < num_visible_tasks; loop++ ) {
    td = visible_tasks[loop];
    if ( td->timer_on ) {
      td->timer_on = 0;
      time ( &now );
      diff = now - td->on_since;
      td->todays_entry->seconds += diff;
      td->on_since = 0;
      new_icon = 0;
      num_timing--;
    }
  }
  td = visible_tasks[st];
  td->timer_on = 1;
  time ( &td->on_since );
  if ( td->todays_entry == NULL )
    td->todays_entry = taskNewTimeEntry ( td->task, today_year,
      today_mon, today_mday );
  update_list ();
  num_timing = 1;
  if ( new_icon )
    gdk_window_set_icon ( GTK_WIDGET ( main_window )->window,
       NULL, appicon, appicon_mask );
  update_list ();
  update_toolbar_buttons ();
}

science_goal_callback(Widget w, XtPointer client_data,
			   XtPointer call_data)
{
  size_t to = (size_t) client_data;
  Boolean b;

  XtVaGetValues(science_help_toggle, XtNstate, &b, NULL);
  if (b == TRUE) {
    popup_help_dialog_typed(advance_name_translation(advance_by_number(to)),
                            HELP_TECH);
  } else {
    dsend_packet_player_tech_goal(&client.conn, to);
  }
}

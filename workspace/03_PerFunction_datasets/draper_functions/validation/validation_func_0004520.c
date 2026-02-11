xaw_key_open_economy_report(Widget w, XEvent *event, String *argv, Cardinal *argc)
{
  if (can_client_change_view()
      && is_menu_item_active(MENU_REPORT, MENU_REPORT_ECONOMY)) {
    economy_report_dialog_popup(FALSE);
  }
}

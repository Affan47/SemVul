diplomacy_dialog_erase_clause_callback(Widget w, XtPointer client_data,
					    XtPointer call_data)
{
  struct Diplomacy_dialog *pdialog = (struct Diplomacy_dialog *) client_data;
  XawListReturnStruct *ret = XawListShowCurrent(pdialog->dip_clauselist);

  if (ret->list_index != XAW_LIST_NONE) {
    int i = 0;

    clause_list_iterate(pdialog->treaty.clauses, pclause) {
      if (i == ret->list_index) {
	dsend_packet_diplomacy_remove_clause_req(&client.conn,
						 player_number(pdialog->treaty.plr1),
						 player_number(pclause->from),
						 pclause->type,
						 pclause->value);
	return;
      }
      i++;
    } clause_list_iterate_end;
  }
}

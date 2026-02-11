usdlg_cmd_exec(GtkObject *object, gpointer data,
                           enum usdlg_cmd cmd)
{
  enum unit_select_location_mode loc = (enum unit_select_location_mode) data;
  GtkTreeView *view;
  GtkTreeSelection *selection;
  GtkTreeModel *model;
  GtkTreeIter it;
  gint row;
  struct unit_select_dialog *pdialog = usdlg_get(FALSE);

  fc_assert_ret(pdialog != NULL);
  fc_assert_ret(unit_select_location_mode_is_valid(loc));

  if (!can_client_change_view() || !can_client_control()) {
    return;
  }

  view = GTK_TREE_VIEW(pdialog->tabs[loc].view);
  selection = gtk_tree_view_get_selection(view);

  if (!gtk_tree_selection_get_selected(selection, &model, &it)) {
    log_debug("No selection");
    return;
  }
  gtk_tree_model_get(model, &it, USDLG_COL_ROW_TYPE, &row, -1);

  switch (row) {
  case ROW_UNITTYPE:
    {
      gint loc, utid;
      struct usdata_hash *ushash;
      struct usdata *data;

      gtk_tree_model_get(model, &it, USDLG_COL_LOCATION, &loc,
                         USDLG_COL_UTID, &utid, -1);


      ushash = usdlg_data_new(pdialog->ptile);

      usdata_hash_lookup(ushash, utid, &data);
      if (data != NULL) {
        enum unit_activity act;

        for (act = 0; act < ACTIVITY_LAST; act++) {
          if (!is_real_activity(act)
              || unit_list_size(data->units[loc][act]) == 0) {
            continue;
          }

          unit_list_iterate(data->units[loc][act], punit) {
            usdlg_cmd_exec_unit(punit, cmd);
          } unit_list_iterate_end;
        }
      }


      usdlg_data_destroy(ushash);
    }
    break;
  case ROW_ACTIVITY:
    {
      gint loc, act, utid;
      struct usdata_hash *ushash;
      struct usdata *data;

      gtk_tree_model_get(model, &it, USDLG_COL_ACTIVITY, &act,
                         USDLG_COL_LOCATION, &loc, USDLG_COL_UTID, &utid, -1);

      fc_assert_ret(is_real_activity(act));


      ushash = usdlg_data_new(pdialog->ptile);

      usdata_hash_lookup(ushash, utid, &data);
      if (data != NULL
          && unit_list_size(data->units[loc][act]) != 0) {
        unit_list_iterate(data->units[loc][act], punit) {
          usdlg_cmd_exec_unit(punit, cmd);
        } unit_list_iterate_end;
      }


      usdlg_data_destroy(ushash);
    }
    break;
  case ROW_UNIT:
  case ROW_UNIT_TRANSPORTED:
    {
      gint uid;
      struct unit *punit;

      gtk_tree_model_get(model, &it, USDLG_COL_UID, &uid, -1);

      punit = game_unit_by_number(uid);

      if (!punit) {
        log_debug("Unit vanished (Unit ID %d)!", uid);
        return;
      }

      usdlg_cmd_exec_unit(punit, cmd);
    }
    break;
  }


  unit_focus_update();

  usdlg_refresh(pdialog);
}

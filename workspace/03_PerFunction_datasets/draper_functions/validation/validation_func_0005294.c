_basic_create(E_Config_Dialog *cfd, Evas *evas, E_Config_Dialog_Data *cfdata)
{
   Evas_Coord mw, mh;
   Evas_Object *of, *ol;

   e_dialog_resizable_set(cfd->dia, 1);

   cfdata->evas = e_win_evas_get(cfd->dia->win);

   of = e_widget_table_add(evas, 0);

   cfdata->o_toolbar = e_widget_toolbar_add(evas, 32 * e_scale, 32 * e_scale);
   e_widget_toolbar_scrollable_set(cfdata->o_toolbar, 1);
   _fill_cat_list(cfdata);
   e_widget_table_object_append(of, cfdata->o_toolbar, 0, 0, 2, 1, 1, 1, 1, 0);

   cfdata->l_modules = e_widget_ilist_add(evas, 32 * e_scale, 32 * e_scale, NULL);
   e_widget_ilist_multi_select_set(cfdata->l_modules, EINA_TRUE);
   e_widget_ilist_go(cfdata->l_modules);
   e_widget_size_min_get(cfdata->l_modules, &mw, &mh);
   if (mw < (200 * e_scale)) mw = 200 * e_scale;
   if (mh < (100 * e_scale)) mh = 100 * e_scale;
   e_widget_size_min_set(cfdata->l_modules, mw, mh);
   e_widget_on_change_hook_set(cfdata->l_modules,
                               _widget_list_selection_changed, cfdata);
   e_widget_table_object_append(of, cfdata->l_modules, 0, 1, 2, 1, 1, 1, 1, 1);

   ol = e_widget_button_add(evas, _("Load"), NULL, _btn_cb_load, cfdata, NULL);
   cfdata->b_load = ol;
   e_widget_disabled_set(ol, 1);
   e_widget_table_object_append(of, ol, 0, 2, 1, 1, 1, 1, 1, 0);

   ol = e_widget_button_add(evas, _("Unload"), NULL, _btn_cb_unload, cfdata, NULL);
   cfdata->b_unload = ol;
   e_widget_disabled_set(ol, 1);
   e_widget_table_object_append(of, ol, 1, 2, 1, 1, 1, 1, 1, 0);

   ol = e_widget_textblock_add(evas);
   e_widget_size_min_set(ol, (200 * e_scale), 40 * e_scale);
   cfdata->o_desc = ol;
   e_widget_table_object_append(of, ol, 0, 3, 2, 1, 1, 0, 1, 0);

   e_dialog_resizable_set(cfd->dia, 1);
   e_util_win_auto_resize_fill(cfd->dia->win);
   e_win_centered_set(cfd->dia->win, 1);

   e_widget_focus_set(cfdata->o_toolbar, 1);
   e_widget_toolbar_item_select(cfdata->o_toolbar, 0);

   cfdata->module_update = ecore_event_handler_add(E_EVENT_MODULE_UPDATE, (Ecore_Event_Handler_Cb)_module_update, cfdata);

   return of;
}

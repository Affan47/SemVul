_e_shelf_cb_menu_rename(void *data, E_Menu *m __UNUSED__, E_Menu_Item *mi __UNUSED__)
{
   E_Shelf *es = data;
   if (es->rename_dialog) return;
   es->rename_dialog = e_entry_dialog_show(_("Rename Shelf"), "edit-rename",
                                          _("Name:"), es->name, NULL, NULL,
                                          _e_shelf_cb_menu_rename_yes_cb,
                                          NULL, es);
   e_object_data_set(E_OBJECT(es->rename_dialog), es);
   e_object_del_attach_func_set(E_OBJECT(es->rename_dialog),
                                _e_shelf_cb_menu_rename_cb);
}

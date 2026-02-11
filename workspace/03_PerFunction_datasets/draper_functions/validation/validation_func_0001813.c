on_nodes_check_toggled(GtkCheckMenuItem *checkmenuitem,  gpointer data)
{
  if (gtk_check_menu_item_get_active(checkmenuitem))
    nodes_wnd_show();
  else
    nodes_wnd_hide();
}

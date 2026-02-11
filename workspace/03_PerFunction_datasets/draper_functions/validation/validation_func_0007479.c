onMainMenuHideClicked(GtkMenuItem *menuitem _U_, gpointer user_data)
{
  VisuUiDockWindow *dock;

  g_return_if_fail(user_data);

  dock = (VisuUiDockWindow*)user_data;
  if (dock->window)
    gtk_widget_hide(dock->window);
  dock->show = FALSE;
}

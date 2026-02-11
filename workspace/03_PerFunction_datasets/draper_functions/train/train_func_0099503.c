gtr_notebook_remove_all_pages (GtrNotebook *notebook)
{
  g_return_if_fail (GTR_IS_NOTEBOOK (notebook));

  gtk_container_foreach (GTK_CONTAINER (notebook),
                         (GtkCallback)remove_tab,
                         notebook);
}

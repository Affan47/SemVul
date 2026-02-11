gucharmap_chartable_accessible_connect_widget_destroyed (GtkAccessible *accessible)
{
  if (gtk_accessible_get_widget (accessible))
    {
      g_signal_connect_after (gtk_accessible_get_widget (accessible),
                              "destroy",
                              G_CALLBACK (gucharmap_chartable_accessible_destroyed),
                              accessible);
    }

  GTK_ACCESSIBLE_CLASS (gucharmap_chartable_accessible_parent_class)->connect_widget_destroyed (accessible);
}

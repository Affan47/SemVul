is_gtk_plug (GtkWidget *toplevel)
{
#ifdef GDK_WINDOWING_X11
  return GTK_IS_PLUG(toplevel);
#else
  return FALSE;
#endif
}

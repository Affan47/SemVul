addAnAtomDlg()
{
	GtkWidget* table;
	GtkWidget* button;
	GtkWidget* frame;
	GtkWidget* winTable;
	guint i;
	guint j;
        GtkStyle *button_style;
        GtkStyle *style;


	gchar*** Symb = get_periodic_table();

  winTable = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_modal(GTK_WINDOW(winTable),TRUE);
  gtk_window_set_title(GTK_WINDOW(winTable),_("Select your atom"));
  gtk_window_set_default_size (GTK_WINDOW(winTable),(gint)(ScreenWidth*0.5),(gint)(ScreenHeight*0.4));

  frame = gtk_frame_new (NULL);
  gtk_frame_set_shadow_type( GTK_FRAME(frame),GTK_SHADOW_ETCHED_OUT);
  gtk_container_set_border_width (GTK_CONTAINER (frame), 10);

  gtk_container_add(GTK_CONTAINER(winTable),frame);
  gtk_widget_show (frame);

  table = gtk_table_new(PERIODIC_TABLE_N_ROWS-1,PERIODIC_TABLE_N_COLUMNS,TRUE);
  gtk_container_add(GTK_CONTAINER(frame),table);
  button_style = gtk_widget_get_style(winTable);

  for ( i = 0;i<PERIODIC_TABLE_N_ROWS-1;i++)
	  for ( j = 0;j<PERIODIC_TABLE_N_COLUMNS;j++)
  {
	  if(strcmp(Symb[j][i],"00"))
	  {
	  button = gtk_button_new_with_label(Symb[j][i]);
          style=set_button_style(button_style,button,Symb[j][i]);
          g_signal_connect(G_OBJECT(button), "clicked",
                            (GCallback)addAtom,(gpointer )Symb[j][i]);
	  g_object_set_data(G_OBJECT(button),"WinTable",winTable);
	  gtk_table_attach(GTK_TABLE(table),button,j,j+1,i,i+1,
		  (GtkAttachOptions)(GTK_FILL | GTK_EXPAND) ,
		  (GtkAttachOptions)(GTK_FILL | GTK_EXPAND),
		  1,1);
	  }

  }

  gtk_widget_show_all(winTable);

}

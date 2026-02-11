navi_frame_widget_init_empty (FrameWidget *fw)
{
  GtkWidget *alignment;

  if(gap_debug) printf("navi_frame_widget_init_empty START\n");


  fw->image_id      = -1;
  fw->frame_nr      = -1;
  fw->pv_ptr        = NULL;
  fw->width         = -1;
  fw->height        = -1;
  fw->frame_timestamp = 0;
  fw->frame_filename = NULL;

  fw->vbox = gtk_vbox_new (FALSE, 1);


  fw->hbox = gtk_hbox_new (FALSE, 1);


  fw->event_box = gtk_event_box_new ();
  gtk_container_add (GTK_CONTAINER (fw->event_box), fw->hbox);
  gtk_widget_set_events (fw->event_box, GDK_BUTTON_PRESS_MASK);
  g_signal_connect (G_OBJECT (fw->event_box), "button_press_event",
                    G_CALLBACK (frame_widget_preview_events),
                    fw);

  gtk_box_pack_start (GTK_BOX (fw->vbox), fw->event_box, FALSE, FALSE, 1);


  fw->number_label = gtk_label_new ("######");
  gtk_box_pack_start (GTK_BOX (fw->hbox), fw->number_label, FALSE, FALSE, 2);
  gtk_widget_show (fw->number_label);


  alignment = gtk_alignment_new (0.5, 0.5, 0.0, 0.0);
  gtk_box_pack_start (GTK_BOX (fw->hbox), alignment, FALSE, FALSE, 2);
  gtk_widget_show (alignment);


  fw->pv_ptr = gap_pview_new( naviD->image_width + 4
                                    , naviD->image_height + 4
                                    , NAVI_CHECK_SIZE
                                    , NULL
                                    );

  gtk_widget_set_events (fw->pv_ptr->da_widget, GDK_EXPOSURE_MASK);
  gtk_container_add (GTK_CONTAINER (alignment), fw->pv_ptr->da_widget);
  gtk_widget_show (fw->pv_ptr->da_widget);
  g_signal_connect (G_OBJECT (fw->pv_ptr->da_widget), "event",
                    G_CALLBACK (frame_widget_preview_events),
                    fw);


  fw->time_label = gtk_label_new ("##:##:###");
  gtk_box_pack_start (GTK_BOX (fw->hbox), fw->time_label, FALSE, FALSE, 2);
  gtk_widget_show (fw->time_label);


  gtk_widget_show (fw->hbox);
  gtk_widget_show (fw->event_box);
  gtk_widget_show (fw->vbox);

  if(gap_debug) printf("navi_frame_widget_init_empty END\n");

}

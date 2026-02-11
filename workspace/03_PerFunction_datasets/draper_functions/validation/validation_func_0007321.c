goo_canvas_widget_set_widget (GooCanvasWidget *witem,
			      GtkWidget       *widget)
{
  GooCanvasItemSimple *simple = (GooCanvasItemSimple*) witem;

  if (witem->widget)
    {
      g_object_set_data (G_OBJECT (witem->widget), "goo-canvas-item", NULL);
      gtk_widget_unparent (witem->widget);
      g_object_unref (witem->widget);
      witem->widget = NULL;
    }

  if (widget)
    {
      witem->widget = widget;
      g_object_ref (witem->widget);
      g_object_set_data (G_OBJECT (witem->widget), "goo-canvas-item", witem);

      if (simple->simple_data->visibility <= GOO_CANVAS_ITEM_INVISIBLE)
	gtk_widget_hide (widget);
      else
	gtk_widget_show (widget);

      if (simple->canvas)
	{
	  if (gtk_widget_get_realized (GTK_WIDGET (simple->canvas)))
	    gtk_widget_set_parent_window (widget,
					  simple->canvas->canvas_window);

	  gtk_widget_set_parent (widget, GTK_WIDGET (simple->canvas));
	}
    }
}

cb_expose(GtkWidget *wid, GdkEventExpose *e, gDrawingArea *data)
{
	if (data->cached())
	{
		gdk_window_clear(GTK_WIDGET(wid)->window);
		data->drawBorder();
	}
	else
	{
		if (data->onExpose)
		{
			data->_in_draw_event = true;
			data->onExpose(data,e->area.x,e->area.y,e->area.width,e->area.height);
			data->_in_draw_event = false;
		}
		data->drawBorder();
	}

	return false;
}

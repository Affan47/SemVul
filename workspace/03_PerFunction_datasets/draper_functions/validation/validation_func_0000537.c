sg_drag_motion(GtkWidget *widget, GdkDragContext *context, gint x, gint y, guint time, gControl *data)
{
	bool retval = true;
	int action;
	gControl *source;

	if (!gApplication::allEvents()) return true;


	switch (context->suggested_action)
	{
  	case GDK_ACTION_MOVE:
  		action = gDrag::Move;
  		break;
  	case GDK_ACTION_LINK:
  		action = gDrag::Link;
  		break;
		case GDK_ACTION_COPY:
		default:
			action = gDrag::Copy;
	}

	source = gApplication::controlItem(gtk_drag_get_source_widget(context));
	gDrag::setDropData(action, x, y, source, NULL);

	context = gDrag::enable(context, data, time);

	if (!data->_drag_enter)
	{


		x = 0;
		y = 0;

		if (data->onDrag)
			retval = !data->onDrag(data);
		data->_drag_enter = true;
	}
	else
	{


		if (data->onDragMove)
			retval = !data->onDragMove(data);
	}

	context = gDrag::disable(context);

	if (retval)
	{
		gdk_drag_status(context, context->suggested_action, time);
		return true;
	}

	gDrag::hide(data);
	return false;
}

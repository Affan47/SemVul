DragMotionThis(GdkDragContext *context,
                                 gint x, gint y, guint dragtime) {
	try {
		Point npt(x, y);
		SetDragPosition(SPositionFromLocation(npt, false, false, UserVirtualSpace()));
#if GTK_CHECK_VERSION(3,0,0)
		GdkDragAction preferredAction = gdk_drag_context_get_suggested_action(context);
		GdkDragAction actions = gdk_drag_context_get_actions(context);
#else
		GdkDragAction preferredAction = context->suggested_action;
		GdkDragAction actions = context->actions;
#endif
		SelectionPosition pos = SPositionFromLocation(npt);
		if ((inDragDrop == ddDragging) && (PositionInSelection(pos.Position()))) {


			preferredAction = static_cast<GdkDragAction>(0);
		} else if (actions == static_cast<GdkDragAction>
		        (GDK_ACTION_COPY | GDK_ACTION_MOVE)) {
			preferredAction = GDK_ACTION_MOVE;
		}
		gdk_drag_status(context, preferredAction, dragtime);
	} catch (...) {
		errorStatus = SC_STATUS_FAILURE;
	}
	return FALSE;
}

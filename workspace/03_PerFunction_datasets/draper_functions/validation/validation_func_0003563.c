motion_notify_event(GtkWidget* w, GdkEventMotion* e)
{
	XAP_UnixFrameImpl * pUnixFrameImpl = static_cast<XAP_UnixFrameImpl *>(g_object_get_data(G_OBJECT(w), "user_data"));
	if(e->type == GDK_MOTION_NOTIFY)
	{


		GdkEvent  * eNext = gdk_event_peek();
		if(eNext && eNext->type == GDK_MOTION_NOTIFY)
		{
			g_object_unref(G_OBJECT(e));
			e = reinterpret_cast<GdkEventMotion *>(eNext);
			while(eNext && eNext->type == GDK_MOTION_NOTIFY)
			{
				xxx_UT_DEBUGMSG(("Swallowing drag event \n"));
				gdk_event_free(eNext);
				eNext = gdk_event_get();
				gdk_event_free(reinterpret_cast<GdkEvent *>(e));
				e = reinterpret_cast<GdkEventMotion *>(eNext);
				eNext = gdk_event_peek();
			}
			if(eNext != NULL)
			{
				gdk_event_free(eNext);
			}
		}
	}

	XAP_Frame* pFrame = pUnixFrameImpl->getFrame();
	pUnixFrameImpl->setTimeOfLastEvent(e->time);
	AV_View * pView = pFrame->getCurrentView();
	EV_UnixMouse * pUnixMouse = static_cast<EV_UnixMouse *>(pFrame->getMouse());

	if (pView)
		pUnixMouse->mouseMotion(pView, e);

	return 1;
}

CWINDOW_activate(CWIDGET *ob)
{
	CWINDOW *active;


	if (ob)
	{
		active = CWidget::getWindow(ob);
		for(;;)
		{
			if (active->toplevel)
				break;
			if (GB.CanRaise(active, EVENT_Activate))
				break;
			active = CWidget::getWindow(CWidget::get(QWIDGET(active)->parentWidget()));
		}
	}
	else
		active = 0;

	if (active == CWINDOW_Active)
		return;


	if (CWINDOW_Active)
	{
		GB.Raise(CWINDOW_Active, EVENT_Deactivate, 0);
		CWINDOW_Active = 0;
	}

	if (active)
		GB.Raise(active, EVENT_Activate, 0);

	CWINDOW_Active = active;
}

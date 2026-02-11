setFocus(IGUIElement* element)
{
	if (Focus == element)
	{
		_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
		return false;
	}


	if (element == this)
		element = 0;


	if (element)
		element->grab();


	IGUIElement *currentFocus = 0;
	if (Focus)
	{
		currentFocus = Focus;
		currentFocus->grab();
		SEvent e;
		e.EventType = EET_GUI_EVENT;
		e.GUIEvent.Caller = Focus;
		e.GUIEvent.Element = element;
		e.GUIEvent.EventType = EGET_ELEMENT_FOCUS_LOST;
		if (Focus->OnEvent(e))
		{
			if (element)
				element->drop();
			currentFocus->drop();
			_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
			return false;
		}
		currentFocus->drop();
		currentFocus = 0;
	}

	if (element)
	{
		currentFocus = Focus;
		if (currentFocus)
			currentFocus->grab();


		SEvent e;
		e.EventType = EET_GUI_EVENT;
		e.GUIEvent.Caller = element;
		e.GUIEvent.Element = Focus;
		e.GUIEvent.EventType = EGET_ELEMENT_FOCUSED;
		if (element->OnEvent(e))
		{
			if (element)
				element->drop();
			if (currentFocus)
				currentFocus->drop();
			_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
			return false;
		}
	}

	if (currentFocus)
		currentFocus->drop();

	if (Focus)
		Focus->drop();


	Focus = element;

	return true;
}

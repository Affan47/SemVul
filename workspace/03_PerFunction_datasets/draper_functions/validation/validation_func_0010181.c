findIconWindow(Window win)
{
	LinkedListIterator<Icon> it(iconList);
	for(; it.current() ; it++)
	{
		if(it.current()->getIconWindow() == win)
			return it.current();
	}

	return NULL;
}

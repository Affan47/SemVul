findTransientsToMapOrUnmap(Window win, bool hide)
{
	list<Client*>::iterator iter;

	if(client_list.size())
	{
		for(iter=client_list.begin(); iter!= client_list.end(); iter++)
		{
			if((*iter)->getTransientWindow() == win)
			{
				if(hide)
				{
					if(! (*iter)->isIconified())
						(*iter)->iconify();
				}
				else
				{
					if((*iter)->isIconified())
						(*iter)->unhide();
				}
			}
		}
	}
}

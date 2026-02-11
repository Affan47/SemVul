updateWindowMenu()
{
	char* temp = new char[wm->getMaxDesktops()];
	for(int i=0; i<wm->getMaxDesktops(); i++)
	{
		sprintf(temp, "%d", i);

		insert(temp,"", SEND_TO_DESKTOP);
	}
	delete [] temp;

	updateMenu();

	addToMenuList(this);
}

close ()
{
	if (!menu)
		return;
	make_continue();
	menu=NULL;
	choosebook_button.destroy();
	firstrecite_button.destroy();
	revise_button.destroy();
	rest_button.destroy();
	know_button.destroy();
	shooting_button.destroy();
	typing_button.destroy();
	quit_button.destroy();

	fixed = NULL;
}

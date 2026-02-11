CallBack_menu_change_nickname(GtkWidget* widget)  {
	(void)widget;

	if(global->phase >= PHASE_GAMECREATE)
		interface_create_nicknamewin();
}

Startup_handle(int n)
{
	enum {
		SINGLE_PLAYER_POSITION = 1,
		TUTORIAL_POSITION,
		LVLEDIT_POSITION,
		OPTIONS_POSITION,
		CREDITS_POSITION,
		CONTRIBUTE_POSITION,
		EXIT_FREEDROID_POSITION
	};
	switch (n) {
	case SINGLE_PLAYER_POSITION:
		game_root_mode = ROOT_IS_GAME;
		if (Single_Player_Menu()) {
			return EXIT_MENU;
		}
		break;
	case LVLEDIT_POSITION:
		prepare_level_editor();
		return EXIT_MENU;
		break;
	case TUTORIAL_POSITION:
		game_root_mode = ROOT_IS_GAME;
		skip_initial_menus = 1;
		char fpp[2048];
		find_file("levels.dat", MAP_DIR, fpp, 0);
		LoadShip(fpp, 0);
		PrepareStartOfNewCharacter("TutorialTuxStart");
		skip_initial_menus = 0;
		free(Me.character_name);
		Me.character_name = strdup("TutorialTux");
		return EXIT_MENU;
		break;
	case OPTIONS_POSITION:
		return MENU_OPTIONS;
	case CREDITS_POSITION:
		PlayATitleFile("Credits.title");
		break;
	case CONTRIBUTE_POSITION:
		PlayATitleFile("Contribute.title");
		break;
	case (-1):
	case EXIT_FREEDROID_POSITION:
		Terminate(EXIT_SUCCESS, TRUE);
		break;
	default:
		break;
	}
	return CONTINUE_MENU;
}

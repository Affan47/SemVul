mission_show_goals_close()
{
	if (Goals_screen_bg_bitmap >= 0)
		bm_release(Goals_screen_bg_bitmap);

	if (Goal_complete_bitmap)
		bm_release(Goal_complete_bitmap);

	if (Goal_incomplete_bitmap)
		bm_release(Goal_incomplete_bitmap);

	if (Goal_failed_bitmap)
		bm_release(Goal_failed_bitmap);

	Goals_screen_ui_window.destroy();
	common_free_interface_palette();
	game_flush();
}

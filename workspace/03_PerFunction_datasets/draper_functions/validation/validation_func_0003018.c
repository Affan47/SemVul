process_defend_town_attack_target()
{
	err_when(action_mode2!=ACTION_DEFEND_TOWN_ATTACK_TARGET);
	if(general_defend_mode_process_attack_target())
	{
		action_mode2 = ACTION_DEFEND_TOWN_DETECT_TARGET;
		action_para2 = UNIT_DEFEND_TOWN_DETECT_COUNT;
		action_x_loc2 = action_y_loc2 = -1;
		err_when(action_mode!=ACTION_STOP || action_para || action_x_loc!=-1 || action_y_loc!=-1 || cur_action==SPRITE_ATTACK);
	}
}

del_stop(int stopId, char remoteAction)
{

	if(!remoteAction && remote.is_enable())
	{

		short *shortPtr = (short *) remote.new_send_queue_msg(MSG_U_SHIP_DEL_STOP, 2*sizeof(short));
		*shortPtr = sprite_recno;
		shortPtr[1] = stopId;
		return;
	}


	if(remote.is_enable() && stop_array[stopId-1].firm_recno==0)
		return;

	stop_array[stopId-1].firm_recno = 0;
	stop_defined_num--;
	update_stop_list();

	if(unit_array.selected_recno==sprite_recno)
	{
		if(!remote.is_enable() || nation_recno==nation_array.player_recno || config.show_ai_info)
			info.disp();
	}
}

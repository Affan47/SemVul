lookup_ship_status(net_player *p,int unique_id,int remove)
{
	int idx;

	for(idx=0;idx<p->s_info.num_last_buttons;idx++){
		if(p->s_info.last_buttons_id[idx] == unique_id){
			if(remove){
				remove_ship_status_item(p,idx);
				p->s_info.num_last_buttons--;
			}
			return 1;
		}
	}
	return 0;
}

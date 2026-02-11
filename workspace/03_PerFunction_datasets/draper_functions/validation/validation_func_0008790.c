delete_ioa_timer(ioa_timer_handle th)
{
	if (th) {
		stop_ioa_timer(th);
		timer_event *te = (timer_event *)th;
		if(te->txt) {
			turn_free(te->txt,strlen(te->txt)+1);
			te->txt = NULL;
		}
		turn_free(th,sizeof(timer_event));
	}
}

FMTimerInit( void )
{
	int i;

	for( i = 0 ; i < MAX_2610 ; i++ )
	{
		Timer[i][0] = timer_alloc(timer_callback_2610);
		Timer[i][1] = timer_alloc(timer_callback_2610);
	}
}

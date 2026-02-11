add_base_level(short baseLevel)
{


	int		i;
	int		totalLoc=(max_x +1) * (max_y +1);
	short		*locPtr;
	err_when( max_x == 0 || max_y == 0 || matrix == NULL);

	for( i=0, locPtr=matrix ; i<totalLoc ; i++, locPtr++ )
	{
		*locPtr += baseLevel;
		if(*locPtr < 1)
			*locPtr = 1;
		if(*locPtr >= MAX_COLOR)
			*locPtr = MAX_COLOR-1;
	}
}

get_fd_by_name(char* name){
	int i = 0;
	for(i=0; i<MAX_NUMBER_OF_SENSORS; i++)
	{
		if(sensor[i].name && strcmp((char *)sensor[i].name, name) == 0)
			return sensor[i].fd;
	}
	return -1;
}

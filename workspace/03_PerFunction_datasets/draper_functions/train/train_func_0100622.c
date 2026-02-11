FCEU_MakePath(int type, const char* filebase)
{
	char ret[FILENAME_MAX];

	switch(type)
	{
		case FCEUMKF_MOVIE:
			if(odirs[FCEUIOD_MOVIES])
				return (string)odirs[FCEUIOD_MOVIES] + PSS + filebase;
			else
				return BaseDirectory + PSS + "movies" + PSS + filebase;
			break;
		case FCEUMKF_STATE:
			if(odirs[FCEUIOD_STATES])
				return (string)odirs[FCEUIOD_STATES] + PSS + filebase;
			else
				return BaseDirectory + PSS + "fcs" + PSS + filebase;
			break;
	}
	return ret;
}

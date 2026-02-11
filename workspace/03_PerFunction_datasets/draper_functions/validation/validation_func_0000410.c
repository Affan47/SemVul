Location_locationbytok(char *tok)
{
	locarec	*l;

	for(l=Location->localist; l!=NULL; l=l->next)
	{
		if(isequal(l->city,tok) || isequal(l->state,tok) || isequal(l->country,tok))
			return l;
	}

	return NULL;
}
